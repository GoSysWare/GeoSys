#include "libpanel.h"
#include "gdefine.h"

ListFunctions::ListFunctions()
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ListFunctions::mousePressEvent(QMouseEvent * event)
{
    QListView::mousePressEvent(event);

    if(gTarget->isMonitor()){
        return;
    }

    if(event->button() != Qt::LeftButton){
        return;
    }

    if(gMainModel->prgCurrent == NULL){
        return;
    }

    if(selectedIndexes().isEmpty()){
        return;
    }

    QString mt = "PL-addfb";
    mt += ";";
    mt += libName;
    mt += ";";
    mt += gMainModel->modelFunction.stringList().at(currentIndex().row());

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(mt);
    mimeData->setData("PL-addfb",QByteArray());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction);
}

LibPanel::LibPanel()
{
    cmbLib = new QComboBox;
    listFunctions = new ListFunctions;
    layout = new QVBoxLayout;
    layout->addWidget(cmbLib);
    layout->addWidget(listFunctions);
    setLayout(layout);

    cmbLib->setModel(&gMainModel->modelLibrary);
    listFunctions->setModel(&gMainModel->modelFunction);

    selLibrary(0);
    connect(cmbLib, SIGNAL(currentIndexChanged(int)), this, SLOT(selLibrary(int)));
}

void LibPanel::selLibrary(int id)
{
    listFunctions->libName = cmbLib->currentText();
    gMainModel->updateFuncList(id);
}
