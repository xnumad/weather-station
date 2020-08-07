#ifndef PARSER_H
#define PARSER_H

#include <QRegularExpression>
#include "network.h"

/**
 * @class Parser
 * @brief Analyzes and separates received values
 *
 * Uses QRegularExpression and QRegularExpressionMatch for separating values
 * @date May 2019
 */
class Parser
{
public:
    Parser();
    QString parseTemperature(QString toParse);
    QString parseHumidity(QString toParse);
    QString *parseBoth(QString toParse);

private:
    QRegularExpression *regularExpression = new QRegularExpression("(.*)X(.*)");
    QRegularExpressionMatch *regularExpressionMatch = new QRegularExpressionMatch;
};

#endif // PARSER_H
