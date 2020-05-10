#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game/Game.h"
#include <QMessageBox>
#include <QRegExp>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), loggingWindow(nullptr) {
    ui->setupUi(this);

    showMaximized();
    ui->graphicsView->showMaximized();
    ui->stackedWidget->setCurrentIndex(0);

    gameScene = std::make_shared<ModifiedScene>();
    ui->graphicsView->setScene(gameScene.get());

    settings = new QSettings("settings.conf", QSettings::IniFormat);
    loggingDirection = settings->value("settings/loggingDirection", LOGGING_DIR_FILE).toInt();
    loggingMode = settings->value("settings/loggingMode", LOGGING_MODE_DEFAULT).toInt();

    Game& game = Game::getInstance();
    game.getLogAdapter().setLoggingDirection(loggingDirection);
    game.getLogAdapter().setLoggingMode(loggingMode);
}

MainWindow::~MainWindow() {
    settings->setValue("settings/loggingDirection", loggingDirection);
    settings->setValue("settings/loggingMode", loggingMode);

    delete settings;
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonMap_clicked() {
    Game& game = Game::getInstance();
    if (!game.exist())
        return;

    ui->stackedWidget->setCurrentIndex(1);
    gameScene->updateInterface();
}

void MainWindow::on_buttonSave_clicked() {
    Game& game = Game::getInstance();
    if (!game.exist())
        return;

    QString name = QFileDialog::getSaveFileName(0, "Save Game", "/", "*.game");
    if (name.size() == 0) {
        return;
    }

    QRegExp regExp("*.game");
    regExp.setPatternSyntax(QRegExp::Wildcard);
    if(!regExp.exactMatch(name)) {
        name += ".game";
    }

    auto stdString = name.toStdString();
    if(game.save(stdString) != 0) {
        QMessageBox::critical(this, "Error", "При сохранении что-то пошло не так. Увы!");
        return;
    }
}

void MainWindow::on_buttonLoad_clicked() {
    QString name = QFileDialog::getOpenFileName(0, "Load Game", "/", "*.game");
    if (name.size() == 0) {
        return;
    }

    Game& game = Game::getInstance();
    auto stdString = name.toStdString();
    if (game.load(stdString) != 0) {
        QMessageBox::critical(this, "Error", "Жители Даларана! Поднимите глаза и взгляните на этот странный файл сохранения!");
        return;
    }
    game.getGameFacade().setScene(gameScene);

    ui->stackedWidget->setCurrentIndex(1);
    gameScene->updateInterface();
}

void MainWindow::on_buttonLogging_clicked() {
    loggingWindow = new LoggingWindow();
    loggingWindow->setLoggingDirection(loggingDirection);
    loggingWindow->setLoggingMode(loggingMode);
    loggingWindow->exec();

    if (loggingWindow->checkAccept()) {
        loggingDirection = loggingWindow->getLoggingDirection();
        loggingMode = loggingWindow->getLoggingMode();

        Game::getInstance().getLogAdapter().setLoggingDirection(loggingDirection);
        Game::getInstance().getLogAdapter().setLoggingMode(loggingMode);
    }

    delete loggingWindow;
    loggingWindow = nullptr;
}

void MainWindow::on_buttonExit_clicked() {
    close();
}
