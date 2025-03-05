#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure with all the fields from the CSV file
struct Student {
    int id;
    char name[100];
    char nationality[50];
    char city[50];
    float latitude;
    float longitude;
    char gender[10];
    char ethnic_group[50];
    int age;
    float english_grade;
    float math_grade;
    float sciences_grade;
    float language_grade;
    float portfolio_rating;
    float coverletter_rating;
    float refletter_rating;
};

// Function to read data from the CSV file
int read_csv(const char *filename, struct Student *students, int max_students) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[1024];
    int count = 0;

    // Skip the header row
    fgets(line, sizeof(line), file);

    // Read the student data
    while (fgets(line, sizeof(line), file)) {
        // Remove newline characters
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0)
            continue;  // Skip empty lines

        if (count >= max_students) {
            break;  // Stop if we've reached the max number of students
        }

        // Print the line to debug
        printf("Reading line: %s\n", line);

        // Parse the CSV line into the Student structure
        int parsed = sscanf(line, "%d,%99[^,],%49[^,],%49[^,],%f,%f,%9[^,],%49[^,],%d,%f,%f,%f,%f,%f,%f,%f",
                             &students[count].id, students[count].name, students[count].nationality, students[count].city,
                             &students[count].latitude, &students[count].longitude, students[count].gender,
                             students[count].ethnic_group, &students[count].age, &students[count].english_grade,
                             &students[count].math_grade, &students[count].sciences_grade, &students[count].language_grade,
                             &students[count].portfolio_rating, &students[count].coverletter_rating, &students[count].refletter_rating);

        // Handle the special case where "NA" for ethnic_group might be a placeholder for missing data
        if (strcmp(students[count].ethnic_group, "NA") == 0) {
            strcpy(students[count].ethnic_group, "Unknown");  // or treat it as a missing value
        }

        // Check if parsing succeeded
        if (parsed != 16) {
            fprintf(stderr, "Error parsing line: %s (parsed %d fields, expected 15)\n", line, parsed);
            continue;
        }

        count++;
    }

    fclose(file);
    return count;
}

// Function to display student data
void displayStudents(struct Student *students, int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("Student Records:\n");

    // Header row with tab separation
    printf("ID\tName\tNationality\tCity\tLat\tLon\tGender\tEthnic Group\tAge\tEng Grade\tMath Grade\tSci Grade\tLang Grade\tPortfolio Rating\tCover Letter Rating\tRef Letter Rating\n");

    // Loop to print each student's data
    for (int i = 0; i < count; i++) {
        // Instead of specifying field widths, just use a simpler format
        printf("%d\t%s\t%s\t%s\t%.4f\t%.4f\t%s\t%s\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
               students[i].id, students[i].name, students[i].nationality, students[i].city,
               students[i].latitude, students[i].longitude, students[i].gender, students[i].ethnic_group,
               students[i].age, students[i].english_grade, students[i].math_grade, students[i].sciences_grade,
               students[i].language_grade, students[i].portfolio_rating, students[i].coverletter_rating,
               students[i].refletter_rating);
    }
}

int main() {
    const char *filename = "/Users/devanshpanchal/Desktop/Technische Informatik TUB/home_projects/Student_data_base/student-dataset.csv";  // Change to your file path
    struct Student students[350];  // Set a fixed maximum number of students (e.g., 100)
    int studentCount = read_csv(filename, students, 308);

    if (studentCount < 0) {
        printf("Failed to read the CSV file.\n");
        return 1;
    }

    displayStudents(students, studentCount);

    return 0;
}
