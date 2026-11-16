
#include <stdio.h>
#include <stdlib.h>

// Represents one telemetry record
typedef struct {

    int device_id;
    float temperature;
    float voltage;
    int status;

} TelemetryRecord;

// Represents one node in the linked list
typedef struct Node {

    TelemetryRecord record;

    struct Node *next;

} Node;


int validate_record(TelemetryRecord record) {

    if (record.device_id <= 0) {
        return 0;
    }

    if (record.temperature < -40.0 || record.temperature > 85.0) {
        return 0;
    }

    if (record.voltage < 2.5 || record.voltage > 3.6) {
        return 0;
    }

    if (record.status != 0 && record.status != 1) {
        return 0;
    }

    return 1;
}

int add_record(Node **head, TelemetryRecord record) {

    // Allocate memory for a new node
    Node *new_node = malloc(sizeof(Node));

if (new_node == NULL) {
    printf("Error: Memory allocation failed.\n");
    return 0;
}

    // Store the telemetry record
    new_node->record = record;

    // The new node is currently the last node
    new_node->next = NULL;

    // If the list is empty, this becomes the first node
    if (*head == NULL) {
        *head = new_node;
        return 1;
    }

    // Find the last node
    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    // Connect the last node to the new node
    current->next = new_node;

    return 1;
}

void display_records(Node *head) {

    Node *current = head;

    while (current != NULL) {

        printf("Device ID: %d\n", current->record.device_id);
        printf("Temperature: %.1f C\n", current->record.temperature);
        printf("Voltage: %.1f V\n", current->record.voltage);
        printf("Status: %d\n\n", current->record.status);

        current = current->next;
    }
}

void calculate_statistics(Node *head) {

    Node *current = head;

    int total_records = 0;

    float total_temperature = 0.0;
    float total_voltage = 0.0;

    float highest_temperature = -40.0;
    int highest_temperature_device = 0;

    while (current != NULL) {

        total_records++;

        total_temperature += current->record.temperature;
        total_voltage += current->record.voltage;

        if (current->record.temperature > highest_temperature) {

            highest_temperature = current->record.temperature;

            highest_temperature_device = current->record.device_id;
        }

        current = current->next;
    }

    if (total_records == 0) {
        printf("No valid records available for statistics.\n");
        return;
    }

    float average_temperature = total_temperature / total_records;
    float average_voltage = total_voltage / total_records;

    printf("\n--- Telemetry Statistics ---\n");

    printf("Total valid records: %d\n", total_records);

    printf("Average temperature: %.2f C\n", average_temperature);

    printf("Average voltage: %.2f V\n", average_voltage);

    printf("Highest temperature: %.2f C\n", highest_temperature);

    printf("Device with highest temperature: %d\n",
           highest_temperature_device);
}

void detect_abnormal_readings(Node *head) {

    Node *current = head;

    printf("\n--- Abnormal Reading Detection ---\n");

    while (current != NULL) {

        int abnormal = 0;

        printf("Device %d: ", current->record.device_id);

        if (current->record.temperature > 70.0) {
            printf("High temperature ");
            abnormal = 1;
        }

        if (current->record.voltage < 2.8) {
            printf("Low voltage ");
            abnormal = 1;
        }

        if (current->record.status == 0) {
            printf("Device inactive ");
            abnormal = 1;
        }

        if (abnormal == 0) {
            printf("Normal");
        }

        printf("\n");

        current = current->next;
    }
}

void write_records_to_file(Node *head) {

    FILE *output_file = fopen("output/telemetry_report.txt", "w");

    if (output_file == NULL) {
        printf("Error: Could not create output file.\n");
        return;
    }

    Node *current = head;

    int total_records = 0;
    float total_temperature = 0.0;
    float total_voltage = 0.0;

    float highest_temperature = -40.0;
    int highest_temperature_device = 0;

    fprintf(output_file, "--- Valid Telemetry Records ---\n\n");

    while (current != NULL) {

        fprintf(output_file, "Device ID: %d\n", current->record.device_id);
        fprintf(output_file, "Temperature: %.1f C\n", current->record.temperature);
        fprintf(output_file, "Voltage: %.1f V\n", current->record.voltage);
        fprintf(output_file, "Status: %d\n\n", current->record.status);

        total_records++;

        total_temperature += current->record.temperature;
        total_voltage += current->record.voltage;

        if (current->record.temperature > highest_temperature) {
            highest_temperature = current->record.temperature;
            highest_temperature_device = current->record.device_id;
        }

        current = current->next;
    }

    if (total_records > 0) {

        fprintf(output_file, "--- Telemetry Statistics ---\n");

        fprintf(output_file, "Total valid records: %d\n", total_records);

        fprintf(output_file, "Average temperature: %.2f C\n",
                total_temperature / total_records);

        fprintf(output_file, "Average voltage: %.2f V\n",
                total_voltage / total_records);

        fprintf(output_file, "Highest temperature: %.2f C\n",
                highest_temperature);

        fprintf(output_file, "Device with highest temperature: %d\n",
                highest_temperature_device);
    }

    fprintf(output_file, "\n--- Abnormal Reading Detection ---\n");

    current = head;

    while (current != NULL) {

        int abnormal = 0;

        fprintf(output_file, "Device %d: ", current->record.device_id);

        if (current->record.temperature > 70.0) {
            fprintf(output_file, "High temperature ");
            abnormal = 1;
        }

        if (current->record.voltage < 2.8) {
            fprintf(output_file, "Low voltage ");
            abnormal = 1;
        }

        if (current->record.status == 0) {
            fprintf(output_file, "Device inactive ");
            abnormal = 1;
        }

        if (abnormal == 0) {
            fprintf(output_file, "Normal");
        }

        fprintf(output_file, "\n");

        current = current->next;
    }

    fclose(output_file);

    printf("Telemetry report saved to output/telemetry_report.txt\n");
}

void free_records(Node *head) {

    Node *current = head;

    while (current != NULL) {

        Node *temp = current;

        current = current->next;

        free(temp);
    }
}

int main(void) {

    FILE *file;

    char line[100];

    file = fopen("data/telemetry.txt", "r");

    if (file == NULL) {

        printf("Error: Could not open telemetry file.\n");

        return 1;
    }

    printf("Telemetry Processor Starting...\n\n");

    TelemetryRecord record;
    Node *head = NULL;

while (fgets(line, sizeof(line), file) != NULL) {

    if (sscanf(line, "%d,%f,%f,%d",
            &record.device_id,
            &record.temperature,
            &record.voltage,
            &record.status) == 4) {

        if (!validate_record(record)) {
            printf("Invalid record skipped.\n\n");
            continue;
        }

        if (!add_record(&head, record)) {

    free_records(head);
    fclose(file);

    return 1;
}
    }
}

printf("\n--- Valid Telemetry Records ---\n\n");

display_records(head);

calculate_statistics(head);

detect_abnormal_readings(head);

write_records_to_file(head);

free_records(head);

fclose(file);

return 0;
}