#include "window.h"
#include "sudoko.h"

#include <iostream>
#include <string>
#include <fstream>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPalette>
#include <QMouseEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

/**
 *
 * Window declarations for GUI creation and
 * Handling I/O Operations following Qt Framework
 *
 *
 **/



Window::Window(QWidget *parent) : QWidget(parent)
{

    // Set size of the window
    setFixedSize(362, 392);
    this->setWindowTitle("Sudoku Solver");

    // Creating inital board
    BoardPositions = CreateInitialBoard();


    RenderBoard();

    initialBuild = false;

    // Creating first button
    m_button = new QPushButton("Import", this);

    // Set the geometry of the button
    m_button->setGeometry(40, 362, 80, 30);

    // Set the style using setStyleSheet
    m_button->setStyleSheet(
        "QPushButton {"
        "border: 1px solid black;"
        "color: black;"
        "background-color: transparent;"
        "}"
        "QPushButton:pressed {"
        "background-color: darkgray;"
        "border: 2px solid black;"
        "}");

    // Creating second button
    s_button = new QPushButton("Solve", this);

    // Set the geometry of the button
    s_button->setGeometry(240, 362, 80, 30);

    //Setting the style using setStyleSheet
    s_button->setStyleSheet(
        "QPushButton {"
        "border: 1px solid black;"
        "color: black;"
        "background-color: transparent;"
        "}"
        "QPushButton:pressed {"
        "background-color: darkgray;"
        "border: 2px solid black;"
        "}");

    // Attaching button to import file function
    connect(m_button, &QPushButton::clicked, this, &Window::ImportFile);

    // Attaching button to solve board function
    connect(s_button, &QPushButton::clicked, this, [this]()
            {
                bool result = SudukoSolves(BoardPositions);
                RenderBoard();
            });
}

void Window::ImportFile()
{
    // Open a file dialog for CSV files
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), "", tr("CSV Files (*.csv);;All Files (*)"));

    // Check if the user selected a file
    if (!fileName.isEmpty())
    {
        // Handle file import logic here, such as reading the CSV file
        loadCSVFile(fileName);
    }
}

void Window::loadCSVFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QTextStream in(&file);
    std::vector<std::vector<std::string>> newBoard(9, std::vector<std::string>(9));

    int row = 0;
    while (!in.atEnd() && row < 9)
    {
        QString line = in.readLine();
        QStringList values = line.split(',');

        for (int col = 0; col < values.size() && col < 9; ++col)
        {
            if (values[col].toStdString() == "0")
            {
                newBoard[row][col] = "-";
            }
            else
            {
                newBoard[row][col] = values[col].toStdString();
            }
        }

        row++;
    }

    // Update the board data
    BoardPositions = newBoard;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << BoardPositions[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Rerender the board with the new data
    RenderBoard();
}

void Window::Render()
{
    // Clear the scene to remove old items
    //scene->clear();

    // Define the size of each cell in the grid
    int cellSize = 40; // Each cell is 40x40 pixels

    // Create a 9x9 grid using QGraphicsRectItem
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Create a rectangle item for each cell
            QGraphicsRectItem *rect = new QGraphicsRectItem();

            // Set the position and size of the rectangle
            rect->setRect(col * cellSize, row * cellSize, cellSize, cellSize);

            // Set a black border for the rectangle
            rect->setPen(QPen(Qt::black));
            rect->setBrush(QBrush(Qt::NoBrush));

            // Get the value from the board
            std::string value = BoardPositions[row][col];

            // Remove the old text item if it exists
            if (board[row][col] != nullptr)
            {
                scene->removeItem(board[row][col]);
                delete board[row][col]; // Free memory of the old item
            }

            // Create a new QGraphicsTextItem for the value
            QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(value));

            // Store the text item
            board[row][col] = textItem;

            // Set the position of the text in the center of the cell
            int xPos = col * cellSize + cellSize / 4; // Adjust for padding
            int yPos = row * cellSize + cellSize / 4;
            textItem->setPos(xPos, yPos);

            // Set font and color for the text
            QFont font("Times", 20);
            textItem->setFont(font);
            textItem->setDefaultTextColor(Qt::black);

            // Add the text item and rectangle to the scene
            scene->addItem(textItem);
            scene->addItem(rect);
        }
    }
}

void Window::RenderBoard()
{
    // Set the window background color to white

    if (initialBuild == true)
    {

        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, Qt::white);
        this->setAutoFillBackground(true);
        this->setPalette(pal);

        // Create a QGraphicsScene
        scene = new QGraphicsScene(this);
    }

    // Define the size of each cell in the grid
    int cellSize = 40; // Each cell is 40x40 pixels

    // Create a 9x9 grid using QGraphicsRectItem
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Create a rectangle item for each cell
            QGraphicsRectItem *rect = new QGraphicsRectItem();

            // Set the position and size of the rectangle
            rect->setRect(col * cellSize, row * cellSize, cellSize, cellSize);

            // Optionally, you can set a pen (border) and a brush (fill color)
            rect->setPen(QPen(Qt::black));       // Black border
            rect->setBrush(QBrush(Qt::NoBrush)); // No fill

            std::string value = BoardPositions[row][col];

            if (board[row][col] != nullptr)
            {
                scene->removeItem(board[row][col]);
                delete board[row][col]; // Free memory of the old item
            }

            // Create a new text item with the input

            // Create a QGraphicsTextItem for each cell
            QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(value));

            board[row][col] = textItem; // Store the new text item

            // Set the position of the text in the center of the cell
            int xPos = col * cellSize + cellSize / 4; // Adjust for padding
            int yPos = row * cellSize + cellSize / 4;
            textItem->setPos(xPos, yPos);

            // Optionally, you can set font, size, and other text properties
            QFont font("Times", 20);
            textItem->setFont(font);
            textItem->setDefaultTextColor(Qt::black);

            // Add the text item to the scene
            scene->addItem(textItem);

            // Add the rectangle to the scene
            scene->addItem(rect);
        }
    }

    if (initialBuild)
    {

        // Create a QGraphicsView to display the scene
        QGraphicsView *view = new QGraphicsView(scene, this);

        // Set the size of the view to fit the grid
        view->setFixedSize(9 * cellSize + 2, 9 * cellSize + 2); // Adjust for borders

        // Position the view inside the window
        view->setGeometry(0, 0, 9 * cellSize, 9 * cellSize);

        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Set the view background color (optional)
        view->setBackgroundBrush(Qt::white);
    }
}

// Want to update board on click and keyboard input

void Window::DrawBoard(std::vector<std::vector<std::string>> &vect)
{
    // Assuming the scene is already set up as a class member
    int cellSize = 40; // Each cell size is 40x40

    // Loop through the 2D vector and add text items to the scene
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Get the character or string to display
            std::string value = vect[row][col];

            // Create a QGraphicsTextItem for each cell
            QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(value));

            // Set the position of the text in the center of the cell
            int xPos = col * cellSize + cellSize / 4; // Adjust for padding
            int yPos = row * cellSize + cellSize / 4;
            textItem->setPos(xPos, yPos);

            // Optionally, you can set font, size, and other text properties
            QFont font("Times", 24);
            textItem->setFont(font);
            textItem->setDefaultTextColor(Qt::black);

            // Add the text item to the scene
            scene->addItem(textItem);
        }
    }
}

// Tracking Clicks across board
void Window::mousePressEvent(QMouseEvent *event)
{
    int cellSize = 40;

    int col = event->x() / cellSize;
    int row = event->y() / cellSize;

    selectedCell = QPoint(col, row);

    posClicked = true;

    return;
}

void Window::keyPressEvent(QKeyEvent *event)
{

    QString input;
    // Checking if click registered
    if (!posClicked || (selectedCell.y() >= 9 || selectedCell.x() >= 9))
    {
        return;
    }

    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9 || (event->key() == Qt::Key_Minus || event->key() == Qt::Key_Space))
    {
        if (event->key() == Qt::Key_Minus || event->key() == Qt::Key_Space)
        {
            input = QString::fromStdString("-");
        }
        else
        {
            input = QString::number(event->key() - Qt::Key_0);
        }
        // Using the selectedCell position to update the board
        int row = selectedCell.y();
        int col = selectedCell.x();

        // If there's already a text item in this cell, remove it
        if (board[row][col] != nullptr)
        {
            // Free memory of the old item
            scene->removeItem(board[row][col]);
            delete board[row][col];
        }

        // Create a new text item with the input
        QGraphicsTextItem *textItem = new QGraphicsTextItem(input);
        board[row][col] = textItem;

        BoardPositions[row][col] = input.toStdString();

        int xPos = col * 40 + 10;
        int yPos = row * 40 + 10;
        textItem->setPos(xPos, yPos);

        QFont font("Times", 20);
        textItem->setFont(font);
        textItem->setDefaultTextColor(Qt::black);

        // Adding the new text item to the scene
        scene->addItem(textItem);

        posClicked = false; // Reset the click state after input
    }

    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        auto b = SudukoSolves(BoardPositions);

        int cellSize = 40; // Each cell size is 40x40

        // Looping through the 2D vector and adding text items to the scene
        for (int row = 0; row < 9; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {
                // Get the character or string to display
                std::string value = BoardPositions[row][col];

                // Creating a QGraphicsTextItem for each cell
                QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromStdString(value));

                if (board[row][col] != nullptr)
                {
                    scene->removeItem(board[row][col]);
                    delete board[row][col];
                }

                // Setting the position of the text in the center of the cell
                int xPos = col * cellSize + cellSize / 4;
                int yPos = row * cellSize + cellSize / 4;
                textItem->setPos(xPos, yPos);

                // Setting Font attributes
                QFont font("Times", 20);
                textItem->setFont(font);
                textItem->setDefaultTextColor(Qt::black);

                // Adding the text item to the scene
                scene->addItem(textItem);
            }
        }
    }

    return;
}
