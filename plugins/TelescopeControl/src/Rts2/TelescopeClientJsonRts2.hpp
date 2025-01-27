/*
 * RTS2 Json stellarium plugin
 * 
 * Copyright (C) 2014-2016 Petr Kubanek
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef TELESCOPECLIENTJSONRTS2_HPP
#define TELESCOPECLIENTJSONRTS2_HPP

#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"
#include "QUrl"

#include "TelescopeClient.hpp"
#include "TelescopeControl.hpp"

#include "StelCore.hpp"

//! RTS2 JSON telescope.
class TelescopeClientJsonRts2 : public TelescopeClient
{
	Q_OBJECT
public:
	TelescopeClientJsonRts2(const QString &name, const QString &params, Equinox eq = EquinoxJ2000);
	~TelescopeClientJsonRts2(void) Q_DECL_OVERRIDE;
	virtual bool isConnected(void) const Q_DECL_OVERRIDE;

	Vec3d getJ2000EquatorialPos(const StelCore* core=Q_NULLPTR) const Q_DECL_OVERRIDE;

	void telescopeGoto(const Vec3d &j2000Pos, StelObjectP selectObject) Q_DECL_OVERRIDE;
	void telescopeSync(const Vec3d &j2000Pos, StelObjectP selectObject) Q_DECL_OVERRIDE;
	bool hasKnownPosition(void) const Q_DECL_OVERRIDE;

protected:
	void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
	virtual QString getTelescopeInfoString(const StelCore* core, const InfoStringGroup& flags) const Q_DECL_OVERRIDE;

private:
	QNetworkAccessManager networkManager;
	QNetworkRequest cfgRequest;
	Equinox equinox;
	QUrl baseurl;
	QString telName;
	bool telReadonly;
	double telLatitude;
	double telLongitude;
	double telAltitude;
	double telTargetDist;
	QNetworkRequest request;
	Vec3d lastPos;
	InterpolatedPosition interpolatedPosition;
	int time_delay;
	int reconnectTimer;
	int refresh_delay;
	qint64 server_micros;

	TelescopeControl *telescopeManager;

	void getReadOnly();
	void setReadOnly(bool readonly);

private slots:
	void refreshTimer();
	void replyFinished(QNetworkReply *reply);
};

#endif // TELESCOPECLIENTJSONRTS2_HPP
