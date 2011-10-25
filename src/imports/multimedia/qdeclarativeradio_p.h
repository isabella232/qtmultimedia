/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDECLARATIVERADIO_P_H
#define QDECLARATIVERADIO_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtDeclarative/qdeclarative.h>
#include <qradiotuner.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QDeclarativeRadio : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(Band band READ band WRITE setBand NOTIFY bandChanged)
    Q_PROPERTY(int frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)
    Q_PROPERTY(bool stereo READ stereo NOTIFY stereoStatusChanged)
    Q_PROPERTY(StereoMode stereoMode READ stereoMode WRITE setStereoMode)
    Q_PROPERTY(int signalStrength READ signalStrength NOTIFY signalStrengthChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)
    Q_PROPERTY(int frequencyStep READ frequencyStep NOTIFY bandChanged)
    Q_PROPERTY(int minimumFrequency READ minimumFrequency NOTIFY bandChanged)
    Q_PROPERTY(int maximumFrequency READ maximumFrequency NOTIFY bandChanged)
    Q_ENUMS(State)
    Q_ENUMS(Band)
    Q_ENUMS(Error)
    Q_ENUMS(StereoMode)
    Q_ENUMS(SearchMode)

public:
    enum State {
        ActiveState = QRadioTuner::ActiveState,
        StoppedState = QRadioTuner::StoppedState
    };

    enum Band {
        AM = QRadioTuner::AM,
        FM = QRadioTuner::FM,
        SW = QRadioTuner::SW,
        LW = QRadioTuner::LW,
        FM2 = QRadioTuner::FM2
    };

    enum Error {
        NoError = QRadioTuner::NoError,
        ResourceError = QRadioTuner::ResourceError,
        OpenError = QRadioTuner::OpenError,
        OutOfRangeError = QRadioTuner::OutOfRangeError
    };

    enum StereoMode {
        ForceStereo = QRadioTuner::ForceStereo,
        ForceMono = QRadioTuner::ForceMono,
        Auto = QRadioTuner::Auto
    };

    enum SearchMode {
        SearchFast = QRadioTuner::SearchFast,
        SearchGetStationId = QRadioTuner::SearchGetStationId
    };

    QDeclarativeRadio(QObject *parent = 0);
    ~QDeclarativeRadio();

    QDeclarativeRadio::State state() const;
    QDeclarativeRadio::Band band() const;
    int frequency() const;
    QDeclarativeRadio::StereoMode stereoMode() const;
    int volume() const;
    bool muted() const;

    bool stereo() const;
    int signalStrength() const;
    bool searching() const;

    int frequencyStep() const;
    int minimumFrequency() const;
    int maximumFrequency() const;

    Q_INVOKABLE bool isAvailable() const;

public Q_SLOTS:
    void setBand(QDeclarativeRadio::Band band);
    void setFrequency(int frequency);
    void setStereoMode(QDeclarativeRadio::StereoMode stereoMode);
    void setVolume(int volume);
    void setMuted(bool muted);

    void cancelScan();
    void scanDown();
    void scanUp();
    void tuneUp();
    void tuneDown();
    void searchAllStations(QDeclarativeRadio::SearchMode searchMode = QDeclarativeRadio::SearchFast );

    void start();
    void stop();

Q_SIGNALS:
    void stateChanged(QDeclarativeRadio::State state);
    void bandChanged(QDeclarativeRadio::Band band);
    void frequencyChanged(int frequency);
    void stereoStatusChanged(bool stereo);
    void searchingChanged(bool searching);
    void signalStrengthChanged(int signalStrength);
    void volumeChanged(int volume);
    void mutedChanged(bool muted);
    void stationFound(int frequency, QString stationId);

    void errorChanged();
    void error(QDeclarativeRadio::Error errorCode);

private Q_SLOTS:
    void _q_stateChanged(QRadioTuner::State state);
    void _q_bandChanged(QRadioTuner::Band band);
    void _q_error(QRadioTuner::Error errorCode);

private:
    Q_DISABLE_COPY(QDeclarativeRadio)

    QRadioTuner *m_radioTuner;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QDeclarativeRadio))

QT_END_HEADER

#endif // QDECLARATIVERADIO_P_H