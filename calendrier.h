#include <QApplication>
#include <QCalendarWidget>
#include <QPainter>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

class CustomCalendarDelegate : public QCalendarWidget
{
public:
    CustomCalendarDelegate()
    {}

private:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override
    {
        QCalendarWidget::paintCell(painter, rect, date);

        // Retrieve activities for the current date from the database
        QVector<QString> activities = getActivitiesForDate(date);

        // Customize cell colors based on activity types
        foreach (const QString &activity, activities) {
            QColor color;
            if (activity == "Type1") {
                color = QColor(255, 0, 0); // Red color
            } else if (activity == "Type2") {
                color = QColor(0, 255, 0); // Green color
            } else if (activity == "Type3") {
                color = QColor(0, 0, 255); // Blue color
            } else if (activity == "Type4") {
                color = QColor(255, 255, 0); // Yellow color
            }


                painter->fillRect(rect, color);

        }
    }

    QVector<QString> getActivitiesForDate(const QDate &date) const
    {        QVector<QString> activities;
            QSqlQuery query;
            query.prepare("SELECT act_type FROM activite WHERE act_date = :date");
            query.bindValue(":date", date.toString(Qt::ISODate));

            if (query.exec()) {
                while (query.next()) {
                    activities.append(query.value(0).toString());
                }
            }


        return activities;

}};

