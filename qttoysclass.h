#pragma once

#include <QWidget>
#include "ui_qttoysclass.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <math.h>
#include "openccTranse.h"
#include <qsciscintilla.h>
//using namespace std;

using iter = std::vector<std::string>::const_iterator;
#if  defined   NDEBUG
#define   assert（condition）   （（void）   0） 
#else 
#define assert（condition） _assert（（condition）,  condition,  __FILE__,  __LINE__）

#endif

class QsciScintilla;
class QtToysClass : public QWidget
{
	Q_OBJECT

public:
	QtToysClass(QWidget *parent, QsciScintilla* pEdit);
	~QtToysClass();

	void showEvent(QShowEvent* event);


	void convert_amount(const long double& money);
	void ConvertDecimal(const long double& money);
	//转换小数部分

	void CleanZero(std::vector<std::string>& v1, std::vector<std::string>& v2, const int& length);
	//消零后输出，函数内调用PrintInteger

	bool PrintInteger(iter iter1, iter iter2, iter end);
	//除元，萬，亿外，输出整数部分及单位
	std::string convertText(const std::string text);
	//void test();

private slots:
	void on_upper();
	void on_lower();
	void on_amount();//到大写金额
	void on_s2t();//简转繁体
	void on_t2s();//繁体转简体
	
private:
	Ui::QtToysClass ui;
	QsciScintilla* m_pEdit;
	QString intext_;
	std::ostringstream oss_;
	QString oss2_;
	const size_t maxS2tTextLen_ = 1000'000;//测试后再定最大简繁转换文本长度。
};
