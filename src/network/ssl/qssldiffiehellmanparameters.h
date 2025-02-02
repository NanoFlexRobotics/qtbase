/****************************************************************************
**
** Copyright (C) 2015 Mikkel Krautz <mikkel@krautz.dk>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtNetwork module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QSSLDIFFIEHELLMANPARAMETERS_H
#define QSSLDIFFIEHELLMANPARAMETERS_H

#include <QtNetwork/qssl.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qshareddata.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_SSL

class QIODevice;
class QSslContext;
class QSslDiffieHellmanParametersPrivate;

class QSslDiffieHellmanParameters;
// qHash is a friend, but we can't use default arguments for friends (§8.3.6.4)
Q_NETWORK_EXPORT size_t qHash(const QSslDiffieHellmanParameters &dhparam, size_t seed = 0) noexcept;

#ifndef QT_NO_DEBUG_STREAM
class QDebug;
Q_NETWORK_EXPORT QDebug operator<<(QDebug debug, const QSslDiffieHellmanParameters &dhparams);
#endif

class Q_NETWORK_EXPORT QSslDiffieHellmanParameters
{
public:
    enum Error {
        NoError,
        InvalidInputDataError,
        UnsafeParametersError
    };

    static QSslDiffieHellmanParameters defaultParameters();

    QSslDiffieHellmanParameters();
    QSslDiffieHellmanParameters(const QSslDiffieHellmanParameters &other);
    QSslDiffieHellmanParameters(QSslDiffieHellmanParameters &&other) noexcept : d(other.d) { other.d = nullptr; }
    ~QSslDiffieHellmanParameters();

    QSslDiffieHellmanParameters &operator=(const QSslDiffieHellmanParameters &other);
    QSslDiffieHellmanParameters &operator=(QSslDiffieHellmanParameters &&other) noexcept { swap(other); return *this; }

    void swap(QSslDiffieHellmanParameters &other) noexcept { qt_ptr_swap(d, other.d); }

    static QSslDiffieHellmanParameters fromEncoded(const QByteArray &encoded, QSsl::EncodingFormat format = QSsl::Pem);
    static QSslDiffieHellmanParameters fromEncoded(QIODevice *device, QSsl::EncodingFormat format = QSsl::Pem);

    bool isEmpty() const noexcept;
    bool isValid() const noexcept;
    Error error() const noexcept;
    QString errorString() const noexcept;

private:
    QSslDiffieHellmanParametersPrivate *d;
    friend class QSslContext;

    bool isEqual(const QSslDiffieHellmanParameters &other) const noexcept;
    friend bool operator==(const QSslDiffieHellmanParameters &lhs, const QSslDiffieHellmanParameters &rhs) noexcept
    { return lhs.isEqual(rhs); }
    friend bool operator!=(const QSslDiffieHellmanParameters &lhs, const QSslDiffieHellmanParameters &rhs) noexcept
    { return !lhs.isEqual(rhs); }

#ifndef QT_NO_DEBUG_STREAM
    friend Q_NETWORK_EXPORT QDebug operator<<(QDebug debug, const QSslDiffieHellmanParameters &dhparam);
#endif
    friend Q_NETWORK_EXPORT size_t qHash(const QSslDiffieHellmanParameters &dhparam, size_t seed) noexcept;
};

Q_DECLARE_SHARED(QSslDiffieHellmanParameters)

#endif // QT_NO_SSL

QT_END_NAMESPACE

#endif
