#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <vector>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

class QPushButton;
class Window : public QWidget
{
public:
    explicit Window(QWidget *parent = 0);
    void DrawBoard(std::vector<std::vector<std::string>> &vect);
    bool getSolvedState();
    void RenderBoard();
    void ImportFile();
    void loadCSVFile(const QString &fileName);
    void Render();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool boardSolved = false;
    bool posClicked = false;
    QPushButton *m_button;
    QPushButton *s_button;
    QGraphicsScene *scene;
    QPoint selectedCell;
    QGraphicsTextItem *board[9][9] = {}; // Track Items across board
    std::vector<std::vector<std::string>> BoardPositions;

    bool initialBuild = true;
};

#endif // WINDOW_H
