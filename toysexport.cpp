#pragma once
//#include <qobject.h>
//#include <qstring.h>
#include <pluginGl.h>
#include <functional>
//#include <qsciscintilla.h>
#include "qttoysclass.h"

#define NDD_EXPORTDLL

#if defined(Q_OS_WIN)
#if defined(NDD_EXPORTDLL)
#define NDD_EXPORT __declspec(dllexport)
#else
#define NDD_EXPORT __declspec(dllimport)
#endif
#endif

#ifdef __cplusplus
	extern "C" {
#endif

	NDD_EXPORT bool NDD_PROC_IDENTIFY(NDD_PROC_DATA* pProcData);
	NDD_EXPORT int NDD_PROC_MAIN(QWidget* pNotepad, const QString& strFileName, std::function<QsciScintilla* ()>getCurEdit);


#ifdef __cplusplus
	}
#endif

bool NDD_PROC_IDENTIFY(NDD_PROC_DATA* pProcData)
{
	if(pProcData == NULL)
	{
		return false;
	}
	pProcData->m_strPlugName = QObject::tr("nddToys Plug");
	pProcData->m_strComment = QObject::tr("a lots of plugin.");

	pProcData->m_version = QString("v0.1");
	pProcData->m_auther = QString("yfz0574");
	return true;
}

//�������ڵ㺯��
int NDD_PROC_MAIN(QWidget* pNotepad, const QString &strFileName, std::function<QsciScintilla*()>getCurEdit)
{
	QsciScintilla* pEdit = getCurEdit();

	//��һЩ�򵥵��ַ��������
	QtToysClass* p = new QtToysClass(pNotepad,pEdit);
	//�����ڹر�ʱ���Ӵ���Ҳ�رա������ָ�����
	p->setWindowFlag(Qt::Window);
	p->show();

	return 0;
}
