#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>

struct Student {
    int rollNumber;
    QString name;
    bool isPresent;
};

class AttendanceManager : public QWidget {
private:
    QTableWidget* tableWidget;
    std::vector<Student> students;

public:
    AttendanceManager(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QLabel* titleLabel = new QLabel("Student Attendance Management");
        layout->addWidget(titleLabel);

        tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(3);
        tableWidget->setHorizontalHeaderLabels({ "Roll Number", "Name", "Attendance" });
        layout->addWidget(tableWidget);

        QPushButton* markButton = new QPushButton("Mark Attendance", this);
        layout->addWidget(markButton);
        connect(markButton, &QPushButton::clicked, this, &AttendanceManager::onMarkAttendanceClicked);

        setLayout(layout);
    }

    void addStudent(int rollNumber, const QString& name) {
        students.push_back({ rollNumber, name, false });
        updateTable();
    }

    void updateTable() {
        tableWidget->setRowCount(students.size());
        for (size_t i = 0; i < students.size(); ++i) {
            QTableWidgetItem* rollNumberItem = new QTableWidgetItem(QString::number(students[i].rollNumber));
            QTableWidgetItem* nameItem = new QTableWidgetItem(students[i].name);
            QTableWidgetItem* attendanceItem = new QTableWidgetItem(students[i].isPresent ? "Present" : "Absent");

            tableWidget->setItem(i, 0, rollNumberItem);
            tableWidget->setItem(i, 1, nameItem);
            tableWidget->setItem(i, 2, attendanceItem);
        }
    }

private slots:
    void onMarkAttendanceClicked() {
        // In a real application, you would implement code to mark attendance based on user input.
        // For this example, we'll just mark the first student present as a demo.
        if (!students.empty()) {
            students[0].isPresent = true;
            updateTable();
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    AttendanceManager manager;
    manager.addStudent(101, "John Doe");
    manager.addStudent(102, "Jane Smith");
    manager.addStudent(103, "Michael Johnson");
    manager.addStudent(104, "Emily Brown");
    manager.show();

    return app.exec();
}
