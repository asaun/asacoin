// Copyright (c) 2011-2014 The Asacoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ASACOIN_QT_ASACOINADDRESSVALIDATOR_H
#define ASACOIN_QT_ASACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AsacoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AsacoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Asacoin address widget validator, checks for a valid asacoin address.
 */
class AsacoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AsacoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ASACOIN_QT_ASACOINADDRESSVALIDATOR_H
