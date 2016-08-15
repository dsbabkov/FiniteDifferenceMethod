#pragma once

#include <QAbstractTableModel>
#include <armadillo>

class ResultsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ResultsModel(QObject *parent = nullptr);

    void setResults(const arma::mat &results);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    arma::mat results_;
};
