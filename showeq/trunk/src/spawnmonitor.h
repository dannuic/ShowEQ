/*
 * spawnmonitor.h
 * 
 * ShowEQ Distributed under GPL
 * http://seq.sourceforge.net/
 *
 * Borrowed from:  SINS Distributed under GPL
 * Portions Copyright 2001 Zaphod (dohpaz@users.sourceforge.net). 
 *
 * For use under the terms of the GNU General Public License, 
 * incorporated herein by reference.
 *
 */

#ifndef SPAWNMONITOR_H
#define SPAWNMONITOR_H

// unfortunately, Qt's notions of time aren't convenient enough to use for something
//	like spawn timing, since QTime doesn't have any simple way to subtract 2 times
//	that might be more than a full day apart... I rely on the functions in "time.h"
//	for now...
//
//	since we're only really interested in holding timestamps in wall-clock time
//	for spawn points, we don't do any funky real-time -> EQ-time conversions.
//	the first instantiation of the "SpawnPoint" class, m_spawnTime will contain the
//	actual time it is at the time of instantiation, later we get updated by the
//  SpawnMonitor to reflect that spawn point's cycle time and set m_diffTime
//
//	the SpawnMonitor contains one IntDict holding a SpawnPoint for every new
//	spawn that comes in... if a spawn occurs for a SpawnPoint that already exists
//	in "m_spawns", then that SpawnPoint is moved to "m_points" and is promoted
//	to an actual spawn point and deleted from "m_spawns"...
//
//	this is experimental, since it's quite possible there might be false positives
//	because the spawns are random... a few false positivies are acceptable provided
//	there is some utility in the spawn timing functionality... i will probably try
//	to derive some test to weed out the false positives based on how old they are:
//	i.e. if a spawn point in m_points doesn't get an update for over 2 weeks, remove
//	it... i don't know enough yet to determine what length is "too old", since there
//	are rumored to be very rare, yet static, spawns in EQ

#include <time.h>
#include <qobject.h>
#include <qasciidict.h>
#include "spawn.h"
#include "zonemgr.h"
#include "spawnshell.h"

class SpawnPoint: public Item
{
public:
  SpawnPoint(uint16_t spawnID, const EQPoint& loc, 
	     const QString& name = "", time_t diffTime = 0, 
	     uint32_t count = 1);

  virtual ~SpawnPoint() { }
  
  unsigned char age() const;
  long secsLeft() const { return m_diffTime - ( time( 0 ) - m_deathTime ); }
  
  static QString key( int x, int y, int z );
  static QString key( const EQPoint& l ) { return key( l.x(), l.y(), l.z() ); }
  QString key() const { return key( x(), y(), z() ); }
  
  QString name() const { return m_name; }
  void setName( const QString& newName ) { m_name = newName; }
  
  QString last() const { return m_last; }
  int32_t count() const { return m_count; }

  Spawn* getSpawn() const;
  
  // protected:
  time_t m_spawnTime;
  time_t m_deathTime;
  time_t m_diffTime;
  uint32_t m_count;
  QString m_name;
  QString m_last;
  uint16_t m_lastID;
};

class SpawnMonitor: public QObject
{
Q_OBJECT
public:
  SpawnMonitor::SpawnMonitor(ZoneMgr* zoneMgr, SpawnShell* spawnShell, 
			     QObject* parent = 0, 
			     const char* name = "spawnmonitor" );
 
  const QAsciiDict<SpawnPoint>& spawnPoints() { return m_points; }
  const QAsciiDict<SpawnPoint>& spawns() { return m_spawns; }
 
public slots:
  void setName(const SpawnPoint* sp, const QString& name);
  void setModified( SpawnPoint* changedSp );
  void newSpawn(const Item* item );
  void killSpawn(const Item* item );
  void zoneChanged( const QString& newZoneName );
  void zoneEnd( const QString& newZoneName );
  void saveSpawnPoints();
  void loadSpawnPoints();

signals:
  void newSpawnPoint( const SpawnPoint* spawnPoint );
  void clearSpawnPoints();
 
protected:
  void restartSpawnPoint( SpawnPoint* spawnPoint );
  void checkSpawnPoint(const Spawn* spawn );
 
  SpawnShell* m_spawnShell;
  QString m_zoneName;
  QAsciiDict<SpawnPoint> m_spawns;
  QAsciiDict<SpawnPoint> m_points;
  bool m_modified;
};

#endif
