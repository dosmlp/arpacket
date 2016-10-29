#include "MACTableModel.h"

MACTableModel::MACTableModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant MACTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return 0;
}

QModelIndex MACTableModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return QModelIndex();
}

QModelIndex MACTableModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    return QModelIndex();
}

int MACTableModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int MACTableModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool MACTableModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return 0;
}

bool MACTableModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void MACTableModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant MACTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool MACTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool MACTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return 0;
}

bool MACTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return 0;
}

bool MACTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return 0;
}
