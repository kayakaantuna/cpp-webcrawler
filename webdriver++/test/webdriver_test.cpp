#include "environment.h"
#include <webdriverxx/webdriver.h>
#include <gtest/gtest.h>

namespace test {

using namespace webdriverxx;

TEST(WebDriver, CreatesSession) {
	Client client(GetWebDriverUrl());
	size_t number_of_sessions_before = client.GetSessions().size();
	WebDriver testee = CreateDriver();
	size_t number_of_sessions_after = client.GetSessions().size();
	ASSERT_EQ(number_of_sessions_before + 1, number_of_sessions_after);
}

TEST(WebDriver, DeletesSessionOnDestruction) {
	Client client(GetWebDriverUrl());
	size_t number_of_sessions_before = 0;
	{
		WebDriver testee = CreateDriver();
		number_of_sessions_before = client.GetSessions().size();
	}
	size_t number_of_sessions_after = client.GetSessions().size();
	ASSERT_EQ(number_of_sessions_before - 1, number_of_sessions_after);
}

TEST(WebDriver, IsCopyable) {
	WebDriver driver1(GetDriver());
	const WebDriver driver2 = driver1;
	WebDriver driver3 = driver1;
	driver3 = driver2;
	ASSERT_NO_THROW(GetDriver().GetSessions());
	ASSERT_NO_THROW(driver1.GetSessions());
	ASSERT_NO_THROW(driver2.GetSessions());
	ASSERT_NO_THROW(driver3.GetSessions());
}

TEST(WebDriver, CopyableToClient) {
	WebDriver driver = GetDriver();
	Client client = driver;
	ASSERT_NO_THROW(client.GetSessions());
	ASSERT_NO_THROW(driver.GetSessions());
}

TEST(WebDriver, CopyableToSession) {
	WebDriver driver = GetDriver();
	Session session = driver;
	ASSERT_NO_THROW(session.GetWindows());
	ASSERT_NO_THROW(driver.GetWindows());
}

TEST(WebDriver, AndSatelliteObjectsHasNoLifetimeIssues) {
	// It is too expensive to restart the driver ->
	// try to test all objects in one test.
	WebDriver& driver = GetDriver();
	driver.Navigate(GetTestPageUrl("webdriver.html"));

	Element body = driver.FindElement(ByTag("body"));
	{
		Window window = driver.GetCurrentWindow();
		{
			Session session = driver;
			{
				Client client = driver;
				{
					WebDriver local_driver = driver;
					GetFreshDriver(); // Destroy global instance
					ASSERT_NO_THROW(local_driver.GetSessions());
					ASSERT_NO_THROW(local_driver.GetWindows());
					ASSERT_NO_THROW(local_driver.FindElement(ByTag("input")));
				}
				ASSERT_NO_THROW(client.GetSessions());
			}
			ASSERT_NO_THROW(session.GetWindows());
			ASSERT_NO_THROW(session.FindElement(ByTag("input")));
		}
		ASSERT_NO_THROW(window.GetSize());
	}
	ASSERT_NO_THROW(body.FindElement(ByTag("input")));
}

} // namespace test
