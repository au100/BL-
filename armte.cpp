//==============================================================================
#include "armte.h"
#include "ui_armte.h"
//------------------------------------------------------------------------------
#include <QStyleFactory>
//------------------------------------------------------------------------------
#include "src/model/model.h"
#include "src/view/tabs/bdmbiospe.h"
#include "src/view/tabs/keys.h"
#include "src/view/tabs/series.h"
#include "src/view/tabs/tos.h"
#include "src/view/Integrity/integrity.h"
#include "src/view/about/about.h"
#include "src/view/simpleforms/addstorage.h"
#include "src/view/armconfig/localconfig.h"
#include "src/model/model.h"
#include "src/view/addchange/importseries.h"
#include "common/paterns.h"
#include "common/logger.h"
//------------------------------------------------------------------------------
#include "common/utils.h"
//==============================================================================
ArmTe* ArmTe::_instance = NULL;
//==============================================================================
ArmTe::ArmTe(QWidget *parent)
     : QMainWindow(parent)
     , ui(new Ui::ArmTe)
     , series(new Series(this))
     , keys(new Keys(this))
     , pe(new BdmBiosPe(this, STORAGE_PE))
//     , bios(new BdmBiosPe(this, STORAGE_BIOS))
     , tos(new Tos(this))
     , bdm(new BdmBiosPe(this, STORAGE_BDM))
     , defaultStorage(NULL)
{
   ui->setupUi(this);
   setup();
   _instance = this;
}
//------------------------------------------------------------------------------
ArmTe::~ArmTe()
{
   if(defaultStorage != NULL)
      delete defaultStorage;
   delete ui;
}
//------------------------------------------------------------------------------
void ArmTe::showMessage(QString msg, int timeout)
{
   ui->status->showMessage(msg, timeout);
}
//------------------------------------------------------------------------------
void ArmTe::setup()
{
   checkAnyStorageExists();
   initStorage();
   refresh();
   addTabs();
   makeMenuActions();

   setupTabs();
}
//------------------------------------------------------------------------------
void ArmTe::setupTabs()
{
   ui->actSerie->setChecked(true);
   ui->actKey->setChecked(true);
   ui->actTos->setChecked(true);
   ui->actBDM->setChecked(true);
   ui->actPe->setChecked(true);

   insertTab(keys);
   insertTab(tos);
   insertTab(bdm);
   insertTab(pe);
   insertTab(series);

   ConfigTabs tabs = Config::VisibleTabs();
   if ((tabs & TAB_KEYS) == 0)
   {
      ui->actKey->setChecked(false);
      removeTab(keys);
   }
   if ((tabs & TAB_TOS) == 0)
   {
      ui->actTos->setChecked(false);
      removeTab(tos);
   }
   if ((tabs & TAB_BDM) == 0)
   {
      ui->actBDM->setChecked(false);
      removeTab(bdm);
   }
   if ((tabs & TAB_PE) == 0)
   {
      ui->actPe->setChecked(false);
      removeTab(pe);
   }
   if ((tabs & TAB_SERIES) == 0)
   {
      ui->actSerie->setChecked(false);
      removeTab(series);
   }
}
//------------------------------------------------------------------------------
void ArmTe::checkAnyStorageExists()
{
   StoragesModel& mod = singleton(StoragesModel);
   if (mod.storages().size() == 0)
   {
      AddStorage add;
      do
      {
         MoveToDesktopCenter(&add);
         add.exec();
         if(add.result() != QDialog::Accepted)
         {
            QMessageBox::StandardButton reply =
                  question(
                     "Необходимо создать хранилище",
                     "Вы не можете начать работу с программой, не создав ни"
                     " одного хранилища.\nВернуться к созданию?");
            if (reply != QMessageBox::Yes)
            {
               exit(0);
            }
         }
      } while (add.result() != QDialog::Accepted);

      Config::setStorage(add.getStorageName());
      Config::Save();
   }
}
//------------------------------------------------------------------------------
void ArmTe::checkStorageExist(const QString& storName)
{
   StoragesModel& mod = singleton(StoragesModel);
   Item* itm = mod.storage(storName);
   if(itm == nullptr)
      Config::setStorage(mod.storagesName().at(0));
   singleton(StorageModel).init(Config::Storage());
}
//------------------------------------------------------------------------------
void ArmTe::initStorage()
{
   QString storName;
   StoragesModel& mod = singleton(StoragesModel);
   ui->storage->clear();
   ui->storage->addItems(mod.storagesName());
   if(Config::Storage().length() == 0)
   {
      ui->storage->setCurrentIndex(0);
      storName = ui->storage->currentText();
   }
   else
      storName  = Config::Storage();
   checkStorageExist(storName);
}
//------------------------------------------------------------------------------
void ArmTe::setStorage()
{
   bdm->initTree();
   pe->initTree();
   keys->initTree();
   tos->initTree();
   series->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::makeTab(QWidget* w, QString iconAlias, QString title)
{
   QIcon icon;
   icon.addFile(iconAlias, QSize(), QIcon::Normal, QIcon::Off);
   w->setWindowIcon(icon);
   w->setWindowTitle(title);
}
//------------------------------------------------------------------------------
void ArmTe::removeTab(QWidget* w)
{
   int idx = ui->tab->indexOf(w);
   if(idx != -1)
   {
      ui->tab->removeTab(idx);
      w->setVisible(false);
   }
}
//------------------------------------------------------------------------------
void ArmTe::insertTab(QWidget* w)
{
   ui->tab->insertTab(ui->tab->count(), w, w->windowIcon(), w->windowTitle());
   w->setVisible(true);
   ui->tab->setCurrentWidget(w);
}
//------------------------------------------------------------------------------
void ArmTe::addTabs()
{
   makeTab(series, ":/new/TabIcon/Serie",  tr("Серии"));
   makeTab(keys,   ":/new/TabIcon/Keys",   tr("Ключи"));
   makeTab(pe,     ":/new/TabIcon/Pe",     tr("Установочные образы"));
   makeTab(tos,    ":/new/TabIcon/Tos",    tr("Образы доверенных систем"));
   makeTab(bdm,    ":/new/TabIcon/Bdm",    tr("BDM дистрибутивы"));
}
//------------------------------------------------------------------------------
void ArmTe::makeMenuActions()
{
   //---------------------------------------------------------------------------
   connect(ui->actStorage,       SIGNAL(triggered()),
           this,                 SLOT(addStorage()));
//   connect(ui->actEditStorage,   SIGNAL(triggered()), this, SLOT(editStorage()));
//   connect(ui->actRemoveStorage, SIGNAL(triggered()), this, SLOT(removeStorage()));
   //---------------------------------------------------------------------------
   connect(ui->actSerie,         SIGNAL(triggered()),
           this,                 SLOT(tabSeries()));
   connect(ui->actKey,           SIGNAL(triggered()),
           this,                 SLOT(tabKey()));
//   connect(ui->actBIOS,          SIGNAL(triggered()),
//           this,                 SLOT(tabBios()));
   connect(ui->actPe,            SIGNAL(triggered()),
           this,                 SLOT(tabPe()));
   connect(ui->actTos,           SIGNAL(triggered()),
           this,                 SLOT(tabTos()));
   connect(ui->actBDM,           SIGNAL(triggered()),
           this,                 SLOT(tabBdm()));
   connect(ui->actAbout,         SIGNAL(triggered()),
           this,                 SLOT(about()));
   connect(ui->actOsIntgr,       SIGNAL(triggered()),
           this,                 SLOT(OsIntgr()));
   connect(ui->actPlatformIntgr, SIGNAL(triggered()),
           this,                 SLOT(PlatformIntgr()));
   connect(ui->storage,          SIGNAL(currentTextChanged(QString)),
           this,                 SLOT(changeCurrentStorage(QString)));
   connect(ui->actOptions,       SIGNAL(triggered()),
           this,                 SLOT(localSetting()));
   //---------------------------------------------------------------------------
   connect(ui->actImportSerie,   SIGNAL(triggered()),
           this,                 SLOT(importSerie()));
   //---------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
void ArmTe::localSetting()
{
   LocalConfig local;
   local.exec();
}
//------------------------------------------------------------------------------
void ArmTe::changeCurrentStorage(QString stor)
{
   Config::setStorage(stor);
   Config::Save();
   singleton(StorageModel).init(Config::Storage());
   refresh();
   LOG(LOG_CNG_STRG, Config::User(), stor);
}
//------------------------------------------------------------------------------
void ArmTe::addStorage()
{
   AddStorage add;
   MoveToDesktopCenter(&add);
   add.exec();
   if(add.result() == QDialog::Accepted)
      initStorage();
}
//------------------------------------------------------------------------------
void ArmTe::tabSeries()
{
   toggleTab(ui->actSerie, series, TAB_SERIES);
}
//------------------------------------------------------------------------------
void ArmTe::tabKey()
{
   toggleTab(ui->actKey, keys, TAB_KEYS);
}
//------------------------------------------------------------------------------
//void ArmTe::tabBios()
//{
//   change(bios);
//}
//------------------------------------------------------------------------------
void ArmTe::tabPe()
{
   toggleTab(ui->actPe, pe, TAB_PE);
}
//------------------------------------------------------------------------------
void ArmTe::tabTos()
{
   toggleTab(ui->actTos, tos, TAB_TOS);
}
//------------------------------------------------------------------------------
void ArmTe::tabBdm()
{
   toggleTab(ui->actBDM, bdm, TAB_BDM);
}
//------------------------------------------------------------------------------
void ArmTe::refresh()
{
   bdm->initTree();
   series->initTree();
   keys->initTree();
   pe->initTree();
   tos->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::toggleTab(QAction *action, QWidget *tab_widget, ConfigTabs config_value)
{
   if (!action || !tab_widget)
   {
      return;
   }

   ConfigTabs tabs = Config::VisibleTabs();

   if(action->isChecked())
   {
      insertTab(tab_widget);
      tabs |= config_value;
   }
   else
   {
      removeTab(tab_widget);
      tabs &= ~config_value;
   }

   Config::SetVisibleTabs(tabs);
}
//------------------------------------------------------------------------------
void ArmTe::importSerie()
{
   ImportSeries import(defaultStorage, this);
   if(import.exec() ==  QDialog::Accepted)
   {
      refresh();
   }
}
//------------------------------------------------------------------------------
void ArmTe::about()
{
   About a;
   a.exec();
}
//------------------------------------------------------------------------------
void ArmTe::PlatformIntgr()
{
//   Integrity *intgr = new Integrity(NULL, PlatformIntegrity);
//   intgr->show();
}
//------------------------------------------------------------------------------
void ArmTe::OsIntgr()
{
//   Integrity *intgr = new Integrity(NULL, OsIntegrity);
//   intgr->show();
}
//------------------------------------------------------------------------------
Series& ArmTe::getSeries()
{
   return *series;
}
//------------------------------------------------------------------------------
Keys& ArmTe::getKeys()
{
   return *keys;
}
//------------------------------------------------------------------------------
BdmBiosPe& ArmTe::getPe()
{
   return *pe;
}
//------------------------------------------------------------------------------
Tos& ArmTe::getTos()
{
   return *tos;
}
//------------------------------------------------------------------------------
BdmBiosPe& ArmTe::getBdm()
{
   return *bdm;
}
//------------------------------------------------------------------------------
void ArmTe::refreshSeries()
{
   Instance().series->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::refreshKeys()
{
   return Instance().keys->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::refreshPe()
{
   return Instance().pe->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::refreshTos()
{
   return Instance().tos->initTree();
}
//------------------------------------------------------------------------------
void ArmTe::refreshBdm()
{
   return Instance().bdm->initTree();
<>
}
//==============================================================================
