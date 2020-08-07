#include "parser.h"

Parser::Parser()
{

}
/**
 * @brief Retrieves temperature value of a string
 * @param toParse The string to be parsed
 * @return The substring containing the temperature, split apart from the original string
 *
 * Separates the value before the character "X" using regular expression capturing groups and returns it as QString
 *
 * https://doc.qt.io/qt-5/qregularexpression.html#extracting-captured-substrings
 */
QString Parser::parseTemperature(QString toParse)
{
    *regularExpressionMatch = regularExpression->match(toParse);
    if (!regularExpressionMatch->hasMatch())
        return 0;
    //return 0;
    return regularExpressionMatch->captured(1);
}

/**
 * @brief Retrieves humidity value of a string
 * @param toParse The string to be parsed
 * @return The substring containing the humidity, split apart from the original string
 *
 * Separates the value after the character "X" using regular expression capturing groups and returns it as QString
 *
 * https://doc.qt.io/qt-5/qregularexpression.html#extracting-captured-substrings
 */
QString Parser::parseHumidity(QString toParse)
{
    *regularExpressionMatch = regularExpression->match(toParse);
    if (!regularExpressionMatch->hasMatch())
        return 0;
    return regularExpressionMatch->captured(2);
}

/**
 * @brief Retrieves temperature and humidity values of a string
 * @param toParse The string to be parsed
 * @return The substrings containing the temperature and humidity, split apart from the original string
 *
 * Separates the values before and after the character "X" using regular expression capturing groups and returns them in a static QString array pointer
 *
 * https://doc.qt.io/qt-5/qregularexpression.html#extracting-captured-substrings
 */
QString *Parser::parseBoth(QString toParse)
{
    *regularExpressionMatch = regularExpression->match(toParse);
    if (!regularExpressionMatch->hasMatch())
        return NULL;

    static QString measurement[2] = {
        regularExpressionMatch->captured(1),
        regularExpressionMatch->captured(2)
    };

    return measurement;
}
