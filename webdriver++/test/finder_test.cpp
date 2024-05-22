#include "environment.h"
#include <webdriverxx/webdriver.h>
#include <gtest/gtest.h>

namespace test {

using namespace webdriverxx;

class TestFinder : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		WebDriver& driver = GetDriver();
		driver.Navigate(GetTestPageUrl("finder.html"));
		driver.FindElement(ById("finder_loaded"));
		driver.SetImplicitTimeoutMs(0);
	}

	static void TearDownTestCase() {
		WebDriver& driver = GetDriver();
		driver.SetImplicitTimeoutMs(1000);
	}

	TestFinder() : driver(GetDriver()) {}

	WebDriver driver;
};

TEST_F(TestFinder, CanFindElement) {
	driver.FindElement(ById("test_id"));
}

TEST_F(TestFinder, ThrowsIfElementNotFound) {
	ASSERT_THROW(driver.FindElement(ById("non_existing")), WebDriverException);
}

TEST_F(TestFinder, CanFindMoreThanOneElement) {
	ASSERT_TRUE(0u < driver.FindElements(ByTag("div")).size());
}

TEST_F(TestFinder, ReturnsZeroIfElementsNotFound) {
	ASSERT_EQ(0u, driver.FindElements(ById("non_existing")).size());
}

TEST_F(TestFinder, FindsElementById) {
	driver.FindElement(ById("test_id"));
	ASSERT_EQ(0u, driver.FindElements(ById("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByClassName) {
	driver.FindElement(ByClass("test_class"));
	ASSERT_EQ(0u, driver.FindElements(ByClass("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByCssSelector) {
	driver.FindElement(ByCss("body div#css_selectable"));
	ASSERT_EQ(0u, driver.FindElements(ByCss("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByName) {
	driver.FindElement(ByName("test_name"));
	ASSERT_EQ(0u, driver.FindElements(ByName("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByLinkText) {
	driver.FindElement(ByLinkText("test link text"));
	ASSERT_EQ(0u, driver.FindElements(ByLinkText("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByPartialLinkText) {
	driver.FindElement(ByPartialLinkText("link text"));
	ASSERT_EQ(0u, driver.FindElements(ByPartialLinkText("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByTagName) {
	driver.FindElement(ByTag("body"));
	ASSERT_EQ(0u, driver.FindElements(ByTag("non_existing")).size());
}

TEST_F(TestFinder, FindsElementByXPath) {
	driver.FindElement(ByXPath("//div"));
	ASSERT_EQ(0u, driver.FindElements(ByXPath("//non_existing")).size());
}

TEST_F(TestFinder, OfElementFindsInnerElement) {
	Element outer = driver.FindElement(ById("outer"));
	outer.FindElement(ById("inner"));
}

TEST_F(TestFinder, OfElementDoesNotFindItself) {
	Element outer = driver.FindElement(ById("outer"));
	ASSERT_EQ(0u, outer.FindElements(ById("outer")).size());
}

TEST_F(TestFinder, OfElementDoesNotFindNonExistingInnerElements) {
	Element outer = driver.FindElement(ById("outer"));
	driver.FindElement(ById("next_after_outer"));
	ASSERT_THROW(outer.FindElement(ById("next_after_outer")), WebDriverException);
	ASSERT_EQ(0u, outer.FindElements(ById("next_after_outer")).size());
}

TEST_F(TestFinder, OfElementFindsMoreThanOneInnerElement) {
	ASSERT_EQ(2u, driver.FindElement(ById("outer")).FindElements(ByTag("div")).size());
}

} // namespace test
