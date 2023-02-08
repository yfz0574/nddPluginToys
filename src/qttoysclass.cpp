#pragma once
#include "qttoysclass.h"
//#include <qsciscintilla.h>
#include <QMessageBox>
#include <qscint/scintilla/include/Scintilla.h>

QtToysClass::QtToysClass(QWidget *parent, QsciScintilla* pEdit)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pEdit = pEdit;
}

QtToysClass::~QtToysClass()
{}
void QtToysClass::showEvent(QShowEvent* event)
{
	//qDebug() << "窗口显示啦~";
	intext_= m_pEdit->selectedText();
	
}
void QtToysClass::on_upper()
{
	//QString text = m_pEdit->selectedText();
	QString text = intext_.toUpper();

	m_pEdit->replaceSelectedText(text);
	this->close();
	return;
}

void QtToysClass::on_lower()
{
	//QString text = m_pEdit->selectedText();

	QString text = intext_.toLower();

	m_pEdit->replaceSelectedText(text);
	this->close();
	return;
}

//v1用于保存数值 即数组a中的数，v2则用于保存单位 即数组b中的数
void QtToysClass::convert_amount(const long double& money)
{
	std::vector<std::string> v1, v2;
	int length;

	const std::string a[] = { reinterpret_cast<const char*>(u8"零"),
		reinterpret_cast<const char*>(u8"壹"),
		reinterpret_cast<const char*>(u8"贰"),
		reinterpret_cast<const char*>(u8"叁"),
		reinterpret_cast<const char*>(u8"肆"),
		reinterpret_cast<const char*>(u8"伍"),
		reinterpret_cast<const char*>(u8"陆"),
		reinterpret_cast<const char*>(u8"柒"),
		reinterpret_cast<const char*>(u8"捌"),
		reinterpret_cast<const char*>(u8"玖") };
	//注意：数组下标从零开始

	const std::string b[] = { 
		reinterpret_cast<const char*>(u8""),
		reinterpret_cast<const char*>(u8"拾"),
		reinterpret_cast<const char*>(u8"佰"),
		reinterpret_cast<const char*>(u8"仟"),
		reinterpret_cast<const char*>(u8""), //个位到一万位   
		reinterpret_cast<const char*>(u8"拾"),
		reinterpret_cast<const char*>(u8"佰"),
		reinterpret_cast<const char*>(u8"仟"),
		reinterpret_cast<const char*>(u8""),          //十万位到千万位
		reinterpret_cast<const char*>(u8"拾"),
		reinterpret_cast<const char*>(u8"佰"),
		reinterpret_cast<const char*>(u8"仟")};          //十亿位到千亿位 

	//元，萬，亿不存储在vector中，在其他函数中输出
	//以防止在消零函数中不输出单位元，萬，亿的情况，如10 0001

	if (money == 0)
	{
		//oss_ << "零元";
		oss2_ += reinterpret_cast<const char*>(u8"零元");
		//QMessageBox::information(nullptr, "", oss2_);
		return;
	}
	else if (money < 0)
	{
		oss2_ += reinterpret_cast<const char*>(u8"所转换的金额必须大于0！") ;
		return;
	}
	else if (money < 1)
		length = 0;          //像0.3这样的数字将其位数定义为0
	else
		length = static_cast<int>(log10(money)) + 1;         //位数
	//money必须>=0

	int len = length;
	for (; len; --len)          //len用于控制循环次数，进而防止循环改变length的值
	{
		long long t = static_cast<long long>(money) / pow(10, len - 1);
		v1.push_back(a[t % 10]);              //逆序进入，位数高的在前面
		v2.push_back(b[len - 1]);
	}

	CleanZero(v1, v2, length);   //消零后输出
	ConvertDecimal(money);     //输出小数部分
	

}

void QtToysClass::ConvertDecimal(const long double& money)
{
	long long integer = static_cast<long long>(money);
	double decimal = money - integer;                  //小数部分
	const std::string a[] = { reinterpret_cast<const char*>(u8"零"),reinterpret_cast<const char*>(u8"壹"),
		reinterpret_cast<const char*>(u8"贰"),reinterpret_cast<const char*>(u8"叁"),reinterpret_cast<const char*>(u8"肆"),
		reinterpret_cast<const char*>(u8"伍"),reinterpret_cast<const char*>(u8"陆"),reinterpret_cast<const char*>(u8"柒"),
		reinterpret_cast<const char*>(u8"捌"),reinterpret_cast<const char*>(u8"玖") };

	if (decimal != 0)
	{
		int t = static_cast<int>(decimal * 10);
		if (t != 0)
		{
			
			oss2_ += QString::fromStdString(a[t]) + reinterpret_cast<const char*>(u8"角");
			
		}
		t = (static_cast<int>((decimal) * 100) % 10);
		if (t != 0)
			oss2_ += QString::fromStdString(a[t]) + reinterpret_cast<const char*>(u8"分");
	}
}

void QtToysClass::CleanZero(std::vector<std::string>& v1, std::vector<std::string>& v2, const int& length)
{
	int t;
		if (length == 0)
		oss2_ += reinterpret_cast<const char*>(u8"");
	//money==0的情况已经在Convert函数中讨论过了，此时length为0指像0.3的数字

	else if (length >= 13)
		oss2_ += reinterpret_cast<const char*>(u8"金额数量太大!");
	else if (length >= 9)
	{
		t = length - 8;
		PrintInteger(v1.begin(), v2.begin(), v1.begin() + t);
		oss2_ += reinterpret_cast<const char*>(u8"亿");
		//9到12位的数字不可能都为零，否则数字位数length不可能>=9

		if (PrintInteger(v1.begin() + t, v2.begin() + t, v1.begin() + t + 4))
			oss2_ += reinterpret_cast<const char*>(u8"萬");
		//if语句用于判断5到8位数字是否都为零
		//若都为零，则不输出 "萬"

		PrintInteger(v1.begin() + t + 4, v2.begin() + t + 4, v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"元");
		//不论1到4位的数字是否都为零，"元"都要输出
	}
	else if (length >= 5)
	{
		int t = length - 4;
		PrintInteger(v1.begin(), v2.begin(), v1.begin() + t);
		oss2_ += reinterpret_cast<const char*>(u8"萬");
		PrintInteger(v1.begin() + t, v2.begin() + t, v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"元整");
	}
	else
	{
		PrintInteger(v1.begin(), v2.begin(), v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"元整");
	}
}

//iter1为类型别名，指vector<string>::const_iterator
bool QtToysClass::PrintInteger(iter iter1, iter iter2, iter end)
{
	bool flag = true;
	//falg用于判断这四个数字是否都为零，若在万位的数字为零，即falg为false,则"萬"不输出

	if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"零")) &&
		(*(iter1 + 2) == reinterpret_cast<const char*>(u8"零")) && (*(iter1 + 3) == reinterpret_cast<const char*>(u8"零")))
		flag = false;
	else
	{
		while (iter1 != end)             //v1,v2所存储的元素个数一样
		{
			if (*iter1 != reinterpret_cast<const char*>(u8"零"))
				oss2_ += QString::fromStdString(*(iter1++))+ QString::fromStdString(*(iter2++));
			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 1) == end))
			{
				++iter1;
				++iter2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 1) != end) && (*(iter1 + 1) != reinterpret_cast<const char*>(u8"零")))
			{
				oss2_ += QString::fromStdString(*(iter1++));
				++iter2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 2) == end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"零")))
			{
				iter1 += 2;
				iter2 += 2;
			}

			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 2) != end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"零")) && (*(iter1 + 2) != reinterpret_cast<const char*>(u8"零")))
			{
				oss2_ += QString::fromStdString(*iter1);
				iter1 += 2;
				iter2 += 2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 3) == end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"零")) && (*(iter1 + 2) == reinterpret_cast<const char*>(u8"零")))
			{
				iter1 += 3;
				iter2 += 3;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"零")) && ((iter1 + 3) != end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"零")) && (*(iter1 + 2) == reinterpret_cast<const char*>(u8"零")))
			{
				oss2_ += QString::fromStdString(*iter1);
				iter1 += 3;
				iter2 += 3;
			}
		}
	}
	return flag;
}

void QtToysClass::on_amount() {

   // QString text = m_pEdit->selectedText();
	oss2_ = reinterpret_cast<const char*>(u8"");
	bool ok;
	double val = intext_.toDouble(&ok);   // ok为true说明str为数字，为false说明str为非数字
	if(ok!=true)
	{ 
		this->close();
		return;
	}

    convert_amount(intext_.toDouble());
	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
	this->close();
	return;
}
void QtToysClass::on_s2t() {

	//intext_= m_pEdit->selectedText();
	if (intext_.isEmpty())
	{
		return;
		this->close();
	}
	int codepage = static_cast<int>(m_pEdit->SendScintilla(SCI_GETCODEPAGE,0ul,nullptr ));
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText("暂未支持非UTF8编码的文件！");
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		this->close();
		return;
		
	}

	openccTranse transe;
	oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += "/plugin/nddToys";///STCharacters.ocd2
	transe.configFileName_ = str.toStdString()+"/s2t.json";
	//const std::string& text = reinterpret_cast<const char*>(u8"燕燕于飞差池其羽之子于归远送于野");
	
	try {
			opencc_t od = opencc_open(transe.configFileName_.c_str());
			char* converted = opencc_convert_utf8(od, intext_.toStdString().c_str(), (size_t)-1);
			oss2_ = converted;
			opencc_convert_utf8_free(converted);
			m_pEdit->replaceSelectedText(oss2_);
			this->close();
			return;
		}
	catch (Exception& ex) {
		throw std::runtime_error(ex.what());
		this->close();
		return;
	}
	
}
void QtToysClass::on_t2s() {

	//QString text = m_pEdit->selectedText();
	//intext_ = m_pEdit->selectedText();
	if(intext_.isEmpty())
	{
		this->close();
		return;
	}
	ConversionPtr convert;
	//TextDict dict();
	int codepage = static_cast<int>(m_pEdit->SendScintilla(SCI_GETCODEPAGE, 0ul, nullptr));
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText(reinterpret_cast<const char*>("暂未支持非UTF8编码的文件！"));
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		this->close();
		return;

	}

	openccTranse transe;
	oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += "/plugin/nddToys";
	transe.configFileName_ = str.toStdString() + "/t2s.json";
	try {
		
		//QMessageBox::information(NULL, "提示", "进入了on_t2s() .try");
		opencc_t od = opencc_open(transe.configFileName_.c_str());
		char* converted = opencc_convert_utf8(od, intext_.toStdString().c_str(), (size_t)-1);
		if (converted == nullptr)
		{
			QMessageBox msgBox;
			
			QString  errstr;
			errstr = reinterpret_cast<const char*>(u8"转换失败！原因为：");
			errstr += opencc_error();
			msgBox.setText(errstr);
			//msgBox.setInformativeText("Do you want to save your changes?");
			//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
			//msgBox.setDefaultButton(QMessageBox::Save);
			int ret = msgBox.exec();
			this->close();
			return;
		}
		oss2_ = converted;
		opencc_convert_utf8_free(converted);
		m_pEdit->replaceSelectedText(oss2_);
		this->close();
		return;
	}
	catch (Exception& ex) {
		
		QMessageBox msgBox;
		QString  errstr;
		errstr = reinterpret_cast<const char*>(u8"转换失败！原因为：");
		//errstr += opencc_error();
		errstr += ex.what();
		msgBox.setText(errstr);
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		this->close();
		return;
		//throw std::runtime_error(ex.what());
		//return;
	}





	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
}

openccTranse::openccTranse(){

};
std::string QtToysClass::convertText(const std::string text) {


	std::string res =(const char*) u8"";
	if (text.length() > maxS2tTextLen_)
	{
		res= reinterpret_cast < const char*>(u8"超过最大长度限制");
		return res;
	}
	openccTranse transe;
	res =transe.convertText(text);
	return res;






}


void QtToysClass::on_close()
{

	this->close();
	return;

}


std::string openccTranse::convertText(const std::string text)
{
	const std::string& converted = converter->Convert(text);
	return converted;
};

