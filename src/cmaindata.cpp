#include "..\include\cmaindata.h"

CContainerData::CContainerData(QObject *parent) : QObject(parent)
{

}

CContainerData::~CContainerData()
{

}

CMainData::CMainData(QObject *parent) : QObject(parent)
{

}

CMainData::~CMainData()
{
  while (!container_data_.isEmpty()) {
    delete container_data_.takeFirst();
  };
}
