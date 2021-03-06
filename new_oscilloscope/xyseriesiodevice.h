/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
 * This file is adjusted to fit our usage
 *
 * This class handles data buffer from Audiodevice and updates charts
 * here we access the buffer and process signal as it updates graphs.
 *
 */

#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QtCore/QIODevice>
#include <QtCharts/QChartGlobal>
#include "filter.h"
#include "frequency_plotter.h"
#include "bpm.h"
#include "file_handler.h"
#include "filtergui.h"

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit XYSeriesIODevice(QXYSeries * series,
                              QXYSeries * freq_series,
                              QObject *parent = 0);
    signalProcessing* getSig(){
        return sig;
    }

public slots:
    void recording();

signals:
    void newBpm(int);

protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);

private:
    bool _recording;

    signalProcessing *sig;
    Frequency_plotter *sigFrequency;
    Bpm *sigBpm;
    File_handler sigFile;
    QXYSeries *m_series;
    QXYSeries *m_freq_series;

};

#endif // XYSERIESIODEVICE_H
