#ifndef KEYBOARD_H
#define KEYBOARD_H

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XTest.h>
#else
#error "Unsupported platform"
#endif

#include <iostream>
#include <vector>
#include <string>
#include <QMainWindow>
#include <QIcon>
#include <QPushButton>
#include <QList>
#include <QKeyEvent>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui { class keyboard; }
QT_END_NAMESPACE

class keyboard : public QMainWindow
{
    Q_OBJECT

protected:
    // void keyPressEvent(QKeyEvent *event) override;
    // void keyReleaseEvent(QKeyEvent *event) override;

public:
    keyboard(QWidget *parent = nullptr);
    ~keyboard();

private slots:

    // eng/kr change
    void on_btn58_clicked();
    void on_copy_clicked();
    void on_clear_clicked();

private:
    Ui::keyboard *ui;
    void setButtonStyle(QPushButton* button, const QString& bgColor, const QString& textColor);
    void on_button_pressed(QPushButton* button);
    void on_button_released(QPushButton* button);
    void handleButtonClick(QPushButton* button);
    void appendTextToLabel(const std::string& text);
    void updateTextLabel(const QString& text);
    void handleBackspace();
    void handleTab();
    void handleEnter();
    void handleCapsLock();
    void handleWindows();
    void updateCapsLockButtonStyle();
    void connectAllButtons();

    void appendKoreanText(const QString& text);
    void handleKoreanInput(const QString& text);

#if defined(_WIN32)
    bool isCapsLockOn() {
        return (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
    }
#elif defined(__linux__)
    bool isCapsLockOn() {
        Display* display = XOpenDisplay(nullptr);
        if (display == nullptr) {
            return false;
        }

        char keys_return[32];
        XQueryPointer(display, DefaultRootWindow(display), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, keys_return);
        bool isCapsLockOn = (keys_return[1] & (1 << (XK_Caps_Lock & 0x7))) != 0;

        XCloseDisplay(display);
        return isCapsLockOn;
    }
#endif
    bool caps = false;
    bool shift = false;
    bool lang = false; // false = eng, true = kor

    void setButtonTexts(QList<QPushButton*>& buttons, const std::vector<std::string>& texts);

    void changeLang();
    std::vector<std::string> keytext_eng ={
        "~\n`", "!\n1", "@\n2", "#\n3", "$\n4", "%\n5", "^\n6", "&&\n7", "*\n8", "(\n9", ")\n0", "_\n-", "+\n=", "Backspace",
        "Tab", "Q\nq", "W\nw", "E\ne", "R\nr", "T\nt", "Y\ny", "U\nu", "I\ni", "O\no", "P\np", "{\n[", "}\n]", "\\ \n |",
        "Caps", "A\na", "S\ns", "D\nd", "F\nf", "G\ng", "H\nh", "J\nj", "K\nk", "L\nl", ":\n;", "\n''", "Enter",
        "Shift", "Z\nz", "X\nx", "C\nc", "V\nv", "B\nb", "N\nn", "M\nm", "<\n,", ">\n.", "?\n/", "Shift",
        "Ctrl", "Win", "Alt", "Space", "Kor", "Win", "Menu", "Ctrl"
    };
    std::vector<std::string> keytext_kor ={
        "~\n`", "!\n1", "@\n2", "#\n3", "$\n4", "%\n5", "^\n6", "&&\n7", "*\n8", "(\n9", ")\n0", "_\n-", "+\n=", "Backspace",
        "Tab", "ㅂ", "ㅈ", "ㄷ", "ㄱ", "ㅅ", "ㅛ", "ㅕ", "ㅑ", "ㅒ\nㅐ", "ㅖ\nㅔ", "{\n[", "}\n]", "\\ \n |",
        "Caps", "ㅁ", "ㄴ", "ㅇ", "ㄹ", "ㅎ", "ㅗ", "ㅓ", "ㅏ", "ㅣ", ":\n;", "\n''", "Enter",
        "Shift", "ㅋ", "ㅌ", "ㅊ", "ㅍ", "ㅠ", "ㅜ", "ㅡ", ",", ".", "/", "Shift",
        "Ctrl", "Win", "Alt", "Space", "영어", "Win", "Menu", "Ctrl"
    };

};

#endif // KEYBOARD_H