#pragma once
#include "qttoysclass.h"
//#include <qsciscintilla.h>
#include <QMessageBox>

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
	//qDebug() << "������ʾ��~";
	intext_= m_pEdit->text();
	convert_amount(intext_.toDouble());
	QString outtext;
	outtext.fromStdString(oss_.str());
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(outtext);
	outtext=outtext.toUpper();
	m_pEdit->setText(outtext);
}
void QtToysClass::on_upper()
{
	QString text = m_pEdit->text();
	text = text.toUpper();

	m_pEdit->setText(text);
}

void QtToysClass::on_lower()
{
	QString text = m_pEdit->text();

	text = text.toLower();

	m_pEdit->setText(text);
}

//v1���ڱ�����ֵ ������a�е�����v2�����ڱ��浥λ ������b�е���
void QtToysClass::convert_amount(const long double& money)
{
	std::vector<std::string> v1, v2;
	int length;

	const std::string a[] = { reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"Ҽ"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"½"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��") };
	//ע�⣺�����±���㿪ʼ

	const std::string b[] = { 
		reinterpret_cast<const char*>(u8""),
		reinterpret_cast<const char*>(u8"ʰ"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"Ǫ"),
		reinterpret_cast<const char*>(u8""), //��λ��һ��λ   
		reinterpret_cast<const char*>(u8"ʰ"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"Ǫ"),
		reinterpret_cast<const char*>(u8""),          //ʮ��λ��ǧ��λ
		reinterpret_cast<const char*>(u8"ʰ"),
		reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"Ǫ")};          //ʮ��λ��ǧ��λ 

	//Ԫ���f���ڲ��洢��vector�У����������������
	//�Է�ֹ�����㺯���в������λԪ���f���ڵ��������10 0001

	if (money == 0)
	{
		//oss_ << "��Ԫ";
		oss2_ += reinterpret_cast<const char*>(u8"��Ԫ");
		//QMessageBox::information(nullptr, "", oss2_);
		return;
	}
	else if (money < 0)
	{
		oss2_ += reinterpret_cast<const char*>(u8"��ת���Ľ��������0��") ;
		return;
	}
	else if (money < 1)
		length = 0;          //��0.3���������ֽ���λ������Ϊ0
	else
		length = static_cast<int>(log10(money)) + 1;         //λ��
	//money����>=0

	int len = length;
	for (; len; --len)          //len���ڿ���ѭ��������������ֹѭ���ı�length��ֵ
	{
		long long t = static_cast<long long>(money) / pow(10, len - 1);
		v1.push_back(a[t % 10]);              //������룬λ���ߵ���ǰ��
		v2.push_back(b[len - 1]);
	}

	CleanZero(v1, v2, length);   //��������
	ConvertDecimal(money);     //���С������
	

}

void QtToysClass::ConvertDecimal(const long double& money)
{
	long long integer = static_cast<long long>(money);
	double decimal = money - integer;                  //С������
	const std::string a[] = { reinterpret_cast<const char*>(u8"��"),reinterpret_cast<const char*>(u8"Ҽ"),
		reinterpret_cast<const char*>(u8"��"),reinterpret_cast<const char*>(u8"��"),reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),reinterpret_cast<const char*>(u8"½"),reinterpret_cast<const char*>(u8"��"),
		reinterpret_cast<const char*>(u8"��"),reinterpret_cast<const char*>(u8"��") };

	if (decimal != 0)
	{
		int t = static_cast<int>(decimal * 10);
		if (t != 0)
		{
			
			oss2_ += QString::fromStdString(a[t]) + reinterpret_cast<const char*>(u8"��");
			
		}
		t = (static_cast<int>((decimal) * 100) % 10);
		if (t != 0)
			oss2_ += QString::fromStdString(a[t]) + reinterpret_cast<const char*>(u8"��");
	}
}

void QtToysClass::CleanZero(std::vector<std::string>& v1, std::vector<std::string>& v2, const int& length)
{
	int t;
		if (length == 0)
		oss2_ += reinterpret_cast<const char*>(u8"");
	//money==0������Ѿ���Convert���������۹��ˣ���ʱlengthΪ0ָ��0.3������

	else if (length >= 13)
		oss2_ += reinterpret_cast<const char*>(u8"�������̫��!");
	else if (length >= 9)
	{
		t = length - 8;
		PrintInteger(v1.begin(), v2.begin(), v1.begin() + t);
		oss2_ += reinterpret_cast<const char*>(u8"��");
		//9��12λ�����ֲ����ܶ�Ϊ�㣬��������λ��length������>=9

		if (PrintInteger(v1.begin() + t, v2.begin() + t, v1.begin() + t + 4))
			oss2_ += reinterpret_cast<const char*>(u8"�f");
		//if��������ж�5��8λ�����Ƿ�Ϊ��
		//����Ϊ�㣬����� "�f"

		PrintInteger(v1.begin() + t + 4, v2.begin() + t + 4, v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"Ԫ");
		//����1��4λ�������Ƿ�Ϊ�㣬"Ԫ"��Ҫ���
	}
	else if (length >= 5)
	{
		int t = length - 4;
		PrintInteger(v1.begin(), v2.begin(), v1.begin() + t);
		oss2_ += reinterpret_cast<const char*>(u8"�f");
		PrintInteger(v1.begin() + t, v2.begin() + t, v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"Ԫ��");
	}
	else
	{
		PrintInteger(v1.begin(), v2.begin(), v1.end());
		oss2_ += reinterpret_cast<const char*>(u8"Ԫ��");
	}
}

//iter1Ϊ���ͱ�����ָvector<string>::const_iterator
bool QtToysClass::PrintInteger(iter iter1, iter iter2, iter end)
{
	bool flag = true;
	//falg�����ж����ĸ������Ƿ�Ϊ�㣬������λ������Ϊ�㣬��falgΪfalse,��"�f"�����

	if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"��")) &&
		(*(iter1 + 2) == reinterpret_cast<const char*>(u8"��")) && (*(iter1 + 3) == reinterpret_cast<const char*>(u8"��")))
		flag = false;
	else
	{
		while (iter1 != end)             //v1,v2���洢��Ԫ�ظ���һ��
		{
			if (*iter1 != reinterpret_cast<const char*>(u8"��"))
				oss2_ += QString::fromStdString(*(iter1++))+ QString::fromStdString(*(iter2++));
			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 1) == end))
			{
				++iter1;
				++iter2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 1) != end) && (*(iter1 + 1) != reinterpret_cast<const char*>(u8"��")))
			{
				oss2_ += QString::fromStdString(*(iter1++));
				++iter2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 2) == end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"��")))
			{
				iter1 += 2;
				iter2 += 2;
			}

			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 2) != end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"��")) && (*(iter1 + 2) != reinterpret_cast<const char*>(u8"��")))
			{
				oss2_ += QString::fromStdString(*iter1);
				iter1 += 2;
				iter2 += 2;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 3) == end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"��")) && (*(iter1 + 2) == reinterpret_cast<const char*>(u8"��")))
			{
				iter1 += 3;
				iter2 += 3;
			}
			else if ((*iter1 == reinterpret_cast<const char*>(u8"��")) && ((iter1 + 3) != end) && (*(iter1 + 1) == reinterpret_cast<const char*>(u8"��")) && (*(iter1 + 2) == reinterpret_cast<const char*>(u8"��")))
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
    convert_amount(intext_.toDouble());
	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
}
void QtToysClass::on_s2t() {

	//QString text = m_pEdit->selectedText();
	oss2_ = reinterpret_cast<const char*>(u8"");
	convertText(intext_.toStdString());
	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
}
void QtToysClass::on_t2s() {

	//QString text = m_pEdit->selectedText();
	oss2_ = reinterpret_cast<const char*>(u8"");
	convertText(intext_.toStdString());
	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
}

std::string QtToysClass::convertText(const std::string text) {

	openccTranse trance;
	std::string res =(const char*) u8"";
	if (text.length() > maxS2tTextLen_)
	{
		res= reinterpret_cast < const char*>(u8"������󳤶�����");
		return res;
	}
	res =trance.convertText(text);
	return res;
}


#include "openccTranse.h"
std::string openccTranse::convertText(const std::string text)
{
	const std::string& converted = converter->Convert(text);
	return converted;
};