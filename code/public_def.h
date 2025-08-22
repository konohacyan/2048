#ifndef INC_2048GAME_PUBLIC_DEF_H
#define INC_2048GAME_PUBLIC_DEF_H
#include <QVector>
#include <QSharedPointer>
#include "base_class.h"
using namespace std;

// 简单的XOR加密密钥
extern const string ENCRYPTION_KEY;
extern const string SAVE_FILE_NAME;

extern const string REMOTE_DB_ADDRESS;  // 远程数据库地址
extern const int REMOTE_DB_PORT;       // 远程数据库端口
extern const string REMOTE_DB_USERNAME; // 远程数据库用户名
extern const string REMOTE_DB_PASSWORD; // 远程数据库密码
extern const string DEFAULT_SCHEMA ;// 默认数据库名，根据实际情况修改

using TilePtr = QSharedPointer<Tile>;
typedef struct data_info_2048
{
    int score;  // 积分
    int best;   // 最高数值
    int count;  // 合成次数
    int width;
    int height;
    QVector<QVector<TilePtr>> grid;
    data_info_2048(int w = 4, int h = 4);

    // 只清空积分和棋子数值，不清理棋盘宽度和最高数值
    void clear();
    // 重新调整数组大小
    void resize(int newWidth, int newHeight)
    {
         resizeGrid(newWidth, newHeight);
    }
    // 访问元素
    int atValue(int x, int y) const;

    TilePtr& atTile(const int& x, const int& y);
    void setTile(const int& x, const int& y, TilePtr tile);
    bool isGridFull() const;

private:
    // 调整棋盘大小
    void resizeGrid(int w, int h);

} DataInfo2048;


enum class MoveDirection
{
    Up,
    Down,
    Left,
    Right
};

/**
@brief 摸鱼配色方案
**/
enum class ColorScheme
{
    cDefault,   // 经典主题
    cLightGray, // 极浅灰（接近白色但更柔和）办公室环境，伪装成文档编辑器。
    cLightGreen, // 极浅绿（低调护眼）​类似 IDE 或代码编辑器的背景色，适合伪装成在工作。
    cTerminalBlack, // 终端黑（极简深色）适合搭配暗色终端/编辑器风格（如 VS Code 暗黑主题）
    cPaperBeige,    // 纸质米黄（伪装成笔记软件）​模仿 OneNote/Evernote 的纸张底色，摸鱼时像在记笔记
    cGuiseExecl,    // 伪装Execl（经典办公风格）​完全模仿 Excel 表格样式，完美融入办公场景
};
#endif // INC_2048GAME_PUBLIC_DEF_H
