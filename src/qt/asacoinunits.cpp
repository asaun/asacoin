// Copyright (c) 2011-2013 The Asacoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "asacoinunits.h"

#include "primitives/transaction.h"

#include <QStringList>

AsacoinUnits::AsacoinUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<AsacoinUnits::Unit> AsacoinUnits::availableUnits()
{
    QList<AsacoinUnits::Unit> unitlist;
    unitlist.append(ASA);
    unitlist.append(mASA);
    unitlist.append(uASA);
    return unitlist;
}

bool AsacoinUnits::valid(int unit)
{
    switch(unit)
    {
    case ASA:
    case mASA:
    case uASA:
        return true;
    default:
        return false;
    }
}

QString AsacoinUnits::id(int unit)
{
    switch(unit)
    {
    case ASA: return QString("asa");
    case mASA: return QString("masa");
    case uASA: return QString("uasa");
    default: return QString("???");
    }
}

QString AsacoinUnits::name(int unit)
{
    switch(unit)
    {
    case ASA: return QString("ASA");
    case mASA: return QString("mASA");
    case uASA: return QString::fromUtf8("μASA");
    default: return QString("???");
    }
}

QString AsacoinUnits::description(int unit)
{
    switch(unit)
    {
    case ASA: return QString("Asacoins");
    case mASA: return QString("Milli-Asacoins (1 / 1" THIN_SP_UTF8 "000)");
    case uASA: return QString("Micro-Asacoins (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
    default: return QString("???");
    }
}

qint64 AsacoinUnits::factor(int unit)
{
    switch(unit)
    {
    case ASA:  return 100000000;
    case mASA: return 100000;
    case uASA: return 100;
    default:   return 100000000;
    }
}

int AsacoinUnits::decimals(int unit)
{
    switch(unit)
    {
    case ASA: return 8;
    case mASA: return 5;
    case uASA: return 2;
    default: return 0;
    }
}

QString AsacoinUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 n = (qint64)nIn;
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thin space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');
    return quotient_str + QString(".") + remainder_str;
}


// TODO: Review all remaining calls to AsacoinUnits::formatWithUnit to
// TODO: determine whether the output is used in a plain text context
// TODO: or an HTML context (and replace with
// TODO: asaoinUnits::formatHtmlWithUnit in the latter case). Hopefully
// TODO: there aren't instances where the result could be used in
// TODO: either context.

// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString AsacoinUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString AsacoinUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}


bool AsacoinUnits::parse(int unit, const QString &value, CAmount *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

QString AsacoinUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (AsacoinUnits::valid(unit))
    {
        amountTitle += " ("+AsacoinUnits::name(unit) + ")";
    }
    return amountTitle;
}

int AsacoinUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant AsacoinUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount AsacoinUnits::maxMoney()
{
    return MAX_MONEY;
}
