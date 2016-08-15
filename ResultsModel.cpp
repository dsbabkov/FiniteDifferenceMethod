#include "ResultsModel.h"

using arma::uword;

ResultsModel::ResultsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ResultsModel::setResults(const arma::mat &results)
{
    results_ = results;
    emit layoutChanged();
}

QVariant ResultsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

int ResultsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return static_cast<int>(results_.n_rows);
}

int ResultsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return static_cast<int>(results_.n_cols);
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole){
        return QVariant();
    }

    return results_(static_cast<uword>(index.row()), static_cast<uword>(index.column()));
}
