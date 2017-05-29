#ifndef QT_PROJECT_WIZZARD_CONTENT_PATH_H
#define QT_PROJECT_WIZZARD_CONTENT_PATH_H

#include <set>

#include "qt/window/project_wizzard/QtProjectWizzardContent.h"

class QCheckBox;
class QComboBox;
class QPushButton;

class QtLocationPicker;
class SourceGroupSettings;

class QtProjectWizzardContentPath
	: public QtProjectWizzardContent
{
	Q_OBJECT

public:
	QtProjectWizzardContentPath(std::shared_ptr<SourceGroupSettings> settings, QtProjectWizzardWindow* window);

	// QtSettingsWindow implementation
	virtual void populate(QGridLayout* layout, int& row) override;

	virtual bool check() override;

protected:
	void setTitleString(const QString& title);
	void setHelpString(const QString& help);

	void setFileEndings(const std::set<std::string>& fileEndings);

	std::shared_ptr<SourceGroupSettings> m_settings;

	QtLocationPicker* m_picker;

	bool m_makePathRelativeToProjectFileLocation;

private:
	QString m_titleString;
	QString m_helpString;
	std::set<std::string> m_fileEndings;
};


class QtProjectWizzardContentPathCDB
	: public QtProjectWizzardContentPath
{
	Q_OBJECT

public:
	QtProjectWizzardContentPathCDB(std::shared_ptr<SourceGroupSettings> settings, QtProjectWizzardWindow* window);

	// QtProjectWizzardContent implementation
	virtual void populate(QGridLayout* layout, int& row) override;

	virtual void load() override;
	virtual void save() override;

private slots:
	void pickedCDBPath();
};


class QtProjectWizzardContentPathSourceMaven
	: public QtProjectWizzardContentPath
{
public:
	QtProjectWizzardContentPathSourceMaven(std::shared_ptr<SourceGroupSettings> settings, QtProjectWizzardWindow* window);

	// QtProjectWizzardContent implementation
	virtual void populate(QGridLayout* layout, int& row) override;

	virtual void load() override;
	virtual void save() override;

	virtual std::vector<std::string> getFileNames() const override;

private:
	QCheckBox* m_shouldIndexTests;
};


class QtProjectWizzardContentPathDependenciesMaven
	: public QtProjectWizzardContentPath
{
public:
	QtProjectWizzardContentPathDependenciesMaven(std::shared_ptr<SourceGroupSettings> settings, QtProjectWizzardWindow* window);

	// QtProjectWizzardContent implementation
	virtual void load() override;
	virtual void save() override;
};

#endif // QT_PROJECT_WIZZARD_CONTENT_PATH_H
