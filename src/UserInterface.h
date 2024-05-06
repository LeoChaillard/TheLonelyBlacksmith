#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

class UserInterface
{
public:
protected:
private:

public:
	UserInterface() = default;
	~UserInterface() = default;

	static UserInterface* GetInstance();

	void DisplayWelcome();
	void HandleDisplay();
protected:
private:
	void DisplayMainMenu();
	void DisplayCollectMenu();
	void DisplayCraftMenu();
	void DisplayResourcesMenu();	
	bool IsValidInt(const std::string& strValue);
};

#endif // DISPLAYMANAGER_H

