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

//插件的入口点函数
int NDD_PROC_MAIN(QWidget* pNotepad, const QString &strFileName, std::function<QsciScintilla*()>getCurEdit)
{
	QsciScintilla* pEdit = getCurEdit();

	//做一些简单的字符处理操作
	QtToysClass* p = new QtToysClass(pNotepad,pEdit);
	//主窗口关闭时，子窗口也关闭。避免空指针操作
	p->setWindowFlag(Qt::Window);
	p->show();

	return 0;
}
