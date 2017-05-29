#include "qt/view/QtMainView.h"

#include "qt/window/QtMainWindow.h"

QtMainView::QtMainView()
{
	m_window = std::make_shared<QtMainWindow>();
	m_window->show();
}

QtMainView::~QtMainView()
{
}

QtMainWindow* QtMainView::getMainWindow() const
{
	return m_window.get();
}

void QtMainView::addView(View* view)
{
	m_views.push_back(view);
	m_window->addView(view);
}

void QtMainView::removeView(View* view)
{
	std::vector<View*>::iterator it = std::find(m_views.begin(), m_views.end(), view);
	if (it == m_views.end())
	{
		return;
	}

	m_window->removeView(view);
	m_views.erase(it);
}

void QtMainView::showView(View* view)
{
	m_onQtThread(
		[=]()
		{
			m_window->showView(view);
		}
	);
}

void QtMainView::hideView(View* view)
{
	m_onQtThread(
		[=]()
		{
			m_window->hideView(view);
		}
	);
}

void QtMainView::loadLayout()
{
	m_window->loadLayout();
}

void QtMainView::saveLayout()
{
	m_window->saveLayout();
}

QStatusBar* QtMainView::getStatusBar()
{
	return m_window->statusBar();
}

void QtMainView::setStatusBar(QStatusBar* statusbar)
{
	m_window->setStatusBar(statusbar);
}

void QtMainView::hideStartScreen()
{
	m_onQtThread(
		[=]()
		{
			m_window->hideStartScreen();
		}
	);
}

void QtMainView::setTitle(const std::string& title)
{
	m_onQtThread(
		[=]()
		{
			m_window->setWindowTitle(QString::fromStdString(title));
		}
	);
}

void QtMainView::activateWindow()
{
	m_onQtThread(
		[=]()
		{
			// It's platform dependent which of these commands does the right thing, for now we just use them all at once.
			m_window->setEnabled(true);
			m_window->raise();
			m_window->setFocus(Qt::ActiveWindowFocusReason);
		}
	);
}

void QtMainView::updateRecentProjectMenu()
{
	m_onQtThread(
		[=]()
		{
			m_window->updateRecentProjectMenu();
		}
	);
}

void QtMainView::updateHistoryMenu(const std::vector<SearchMatch>& history)
{
	m_onQtThread(
		[=]()
		{
			m_window->updateHistoryMenu(history);
		}
	);
}

void QtMainView::handleMessage(MessageForceEnterLicense* message)
{
	bool expired = message->licenseExpired;

	m_onQtThread(
		[=]()
		{
			m_window->forceEnterLicense(expired);
		}
	);
}

void QtMainView::handleMessage(MessageProjectEdit* message)
{
	m_onQtThread(
		[=]()
		{
			m_window->editProject();
		}
	);
}

void QtMainView::handleMessage(MessageProjectNew* message)
{
	std::string cdbPath = message->cdbPath;
	std::vector<std::string> headerPaths = message->headerPaths;

	m_onQtThread(
		[=]()
		{
			m_window->newProjectFromCDB(cdbPath, headerPaths);
		}
	);
}

void QtMainView::handleMessage(MessageShowStartScreen* message)
{
	m_onQtThread(
		[=]()
		{
			m_window->showStartScreen();
		}
	);
}
