#include "FileSystemModel.h"

FileSystemModel::FileSystemModel(QObject *parent)
    : QFileSystemModel{parent}
{
    setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    setNameFilters({"*.yaml"});
    setNameFilterDisables(false);
}
