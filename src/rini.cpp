//
// Created by n on 14/11/2026.
//

#include "rini.h"

#include <stdio.h>          // Required for: fopen(), feof(), fgets(), fclose(), fprintf()
#include <stdlib.h>         // Required for: malloc(), calloc(), free()
#include <string.h>         // Required for: memset(), memcpy(), strcmp(), strlen()

//----------------------------------------------------------------------------------
// Defines and macros
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Global variables definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Internal Functions Declaration
//----------------------------------------------------------------------------------
static int rini_read_key(const char *buffer, char *key); // Get key from a buffer line containing key-value-(description)
static int rini_read_value_text(const char *buffer, char *text, char *desc, bool *is_text); // Get value text (and description) from a buffer line

static int rini_text_to_int(const char *text); // Convert text to int value (if possible), same as atoi()

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
// Load data from file (.ini)
// NOTE: Only key-value-description loaded, no empty lines or comments
rini_data rini_load(const char *file_name)
{
    rini_data data = { 0 };
    unsigned int value_counter = 0;

    // Init data to max capacity
    data.capacity = RINI_MAX_ENTRY_CAPACITY;
    data.entries = (rini_entry *)RINI_CALLOC(RINI_MAX_ENTRY_CAPACITY, sizeof(rini_entry));

    if (file_name != NULL)
    {
        FILE *rini_file = fopen(file_name, "rt");

        if (rini_file != NULL)
        {
            char buffer[RINI_MAX_LINE_SIZE] = { 0 };    // Buffer to read every text line

            // First pass to count valid lines
            while (fgets(buffer, RINI_MAX_LINE_SIZE, rini_file))
            {
                // WARNING: fgets() keeps line endings, doesn't have any special options for converting line endings,
                // but on Windows, when reading file 'rt', line endings are converted from \r\n to just \n

                // Skip commented lines and empty lines
                // NOTE: Also skipping sections delimiters
                if ((buffer[0] != RINI_LINE_COMMENT_DELIMITER) &&
                    (buffer[0] != RINI_LINE_SECTION_DELIMITER) &&
                    (buffer[0] != '\n') && (buffer[0] != '\r') && (buffer[0] != '\0')) value_counter++;
            }

            // WARNING: No more values can be stored than its max capacity
            data.count = (value_counter > RINI_MAX_ENTRY_CAPACITY)? RINI_MAX_ENTRY_CAPACITY : value_counter;

            if (data.count > 0)
            {
                rewind(rini_file);
                value_counter = 0;

                // Second pass to read data
                while (fgets(buffer, RINI_MAX_LINE_SIZE, rini_file))
                {
                    // WARNING: fgets() keeps line endings, doesn't have any special options for converting line endings,
                    // but on Windows, when reading file 'rt', line endings are converted from \r\n to just \n

                    // Skip commented lines and empty lines
                    if ((buffer[0] != RINI_LINE_COMMENT_DELIMITER) &&
                        (buffer[0] != RINI_LINE_SECTION_DELIMITER) &&
                        (buffer[0] != '\n') && (buffer[0] != '\r') && (buffer[0] != '\0'))
                    {
                        // Get key identifier string
                        memset(data.entries[value_counter].key, 0, RINI_MAX_KEY_SIZE);
                        rini_read_key(buffer, data.entries[value_counter].key);
                        rini_read_value_text(buffer, data.entries[value_counter].text, data.entries[value_counter].desc, &data.entries[value_counter].is_text);

                        value_counter++;

                        // Stop reading if first count reached to avoid overflow in case count == RINI_MAX_ENTRY_CAPACITY
                        if (value_counter >= data.count) break;
                    }
                }
            }

            fclose(rini_file);
        }
    }

    return data;
}

// Load data from file (.ini) including all comments and empty lines
rini_data rini_load_full(const char *file_name)
{
    rini_data data = { 0 };
    unsigned int value_counter = 0;

    // Init data to max capacity
    data.capacity = RINI_MAX_ENTRY_CAPACITY;
    data.entries = (rini_entry *)RINI_CALLOC(RINI_MAX_ENTRY_CAPACITY, sizeof(rini_entry));

    if (file_name != NULL)
    {
        FILE *rini_file = fopen(file_name, "rt");

        if (rini_file != NULL)
        {
            char buffer[RINI_MAX_LINE_SIZE] = { 0 };    // Buffer to read every text line

            // First pass to count valid lines
            while (fgets(buffer, RINI_MAX_LINE_SIZE, rini_file))
            {
                // WARNING: fgets() keeps line endings, doesn't have any special options for converting line endings,
                // but on Windows, when reading file 'rt', line endings are converted from \r\n to just \n

                // NOTE: Keeping all lines, including comments,
                // useful for files editing without losing information
                if (buffer[0] != '\0') value_counter++;
            }

            // WARNING: No more values can be stored than its max capacity
            data.count = (value_counter > RINI_MAX_ENTRY_CAPACITY)? RINI_MAX_ENTRY_CAPACITY : value_counter;

            if (data.count > 0)
            {
                rewind(rini_file);
                value_counter = 0;

                // Second pass to read data
                while (fgets(buffer, RINI_MAX_LINE_SIZE, rini_file))
                {
                    // WARNING: fgets() keeps line endings, doesn't have any special options for converting line endings,
                    // but on Windows, when reading file 'rt', line endings are converted from \r\n to just \n

                    // NOTE: Keeping all lines, including comments,
                    // useful for files editing without losing information
                    if (buffer[0] != '\0')
                    {
                        if ((buffer[0] == '\n') || (buffer[0] == '\r'))  // Empty line
                        {
                            // Set entry as empty line: NULL, NULL, NULL
                            memset(data.entries[value_counter].key, 0, RINI_MAX_KEY_SIZE);   // NULL
                            memset(data.entries[value_counter].text, 0, RINI_MAX_TEXT_SIZE); // NULL
                            memset(data.entries[value_counter].desc, 0, RINI_MAX_DESC_SIZE); // NULL
                        }
                        else if (buffer[0] == RINI_LINE_COMMENT_DELIMITER)  // Comment line
                        {
                            // Measure comment line length
                            int len = 0;
                            char *buffer_ptr = (char *)buffer + 1; // Skip comment delimiter
                            while ((buffer_ptr[len] != '\0') && (buffer_ptr[len] != '\r') && (buffer_ptr[len] != '\n')) len++;

                            // Set entry as comment
                            memset(data.entries[value_counter].key, 0, RINI_MAX_KEY_SIZE);   // NULL
                            memset(data.entries[value_counter].text, 0, RINI_MAX_TEXT_SIZE); // NULL
                            memset(data.entries[value_counter].desc, 0, RINI_MAX_DESC_SIZE); // NULL
                            if (len == 0)
                            {
                                // Set entry as empty comment: NULL, NULL, " "
                                data.entries[value_counter].desc[0] = ' ';
                            }
                            else
                            {
                                // Set entry as comment: NULL, NULL, "comment"
                                // WARNING: In case of comment line, everything after delimiter is read (including spaces)
                                memcpy(data.entries[value_counter].desc, buffer_ptr, len);
                            }
                        }
                        else
                        {
                            // Get key identifier string
                            memset(data.entries[value_counter].key, 0, RINI_MAX_KEY_SIZE);
                            rini_read_key(buffer, data.entries[value_counter].key);
                            rini_read_value_text(buffer, data.entries[value_counter].text, data.entries[value_counter].desc, &data.entries[value_counter].is_text);
                        }

                        value_counter++;

                        // Stop reading if first count reached to avoid overflow in case count == RINI_MAX_ENTRY_CAPACITY
                        if (value_counter >= data.count) break;
                    }
                }
            }

            fclose(rini_file);
        }
    }

    return data;
}

// Load data from text buffer
// NOTE: Comments and empty lines are ignored
rini_data rini_load_from_memory(const char *text)
{
    #define RINI_MAX_TEXT_LINES     RINI_MAX_ENTRY_CAPACITY*2       // Consider possible comments and empty lines

    rini_data data = { 0 };
    unsigned int value_counter = 0;

    // Init data to max capacity
    data.capacity = RINI_MAX_ENTRY_CAPACITY;
    data.entries = (rini_entry *)RINI_CALLOC(RINI_MAX_ENTRY_CAPACITY, sizeof(rini_entry));

    if (text != NULL)
    {
        // Split text by line-breaks
        const char *lines[RINI_MAX_TEXT_LINES] = { 0 };
        int textSize = (int)strlen(text);
        lines[0] = text;
        int line_counter = 1;

        for (int i = 0, k = 1; (i < textSize) && (line_counter < RINI_MAX_TEXT_LINES); i++)
        {
            if (text[i] == '\n')
            {
                lines[k] = &text[i + 1]; // WARNING: next value is valid?
                line_counter += 1;
                k++;
            }
        }

        // Count possible values in lines
        for (int l = 0; l < line_counter; l++)
        {
            // Skip commented lines and empty lines
            // NOTE: Also skipping sections delimiters
            if ((lines[l][0] != RINI_LINE_COMMENT_DELIMITER) &&
                (lines[l][0] != RINI_LINE_SECTION_DELIMITER) &&
                (lines[l][0] != '\n') && (lines[l][0] != '\r') && (lines[l][0] != '\0')) value_counter++;
        }

        // WARNING: No more values can be stored than its max capacity
        data.count = (value_counter > RINI_MAX_ENTRY_CAPACITY)? RINI_MAX_ENTRY_CAPACITY : value_counter;

        // Process lines to get keys and values
        if (data.count > 0)
        {
            value_counter = 0;

            // Second pass to read data
            for (int l = 0; l < line_counter; l++)
            {
                // Skip commented lines and empty lines
                if ((lines[l][0] != RINI_LINE_COMMENT_DELIMITER) &&
                    (lines[l][0] != RINI_LINE_SECTION_DELIMITER) &&
                    (lines[l][0] != '\n') && (lines[l][0] != '\r') && (lines[l][0] != '\0'))
                {
                    // Get key identifier string
                    memset(data.entries[value_counter].key, 0, RINI_MAX_KEY_SIZE);
                    rini_read_key(lines[l], data.entries[value_counter].key);
                    rini_read_value_text(lines[l], data.entries[value_counter].text, data.entries[value_counter].desc, &data.entries[value_counter].is_text);

                    value_counter++;

                    // Stop reading if first count reached to avoid overflow in case count == RINI_MAX_ENTRY_CAPACITY
                    if (value_counter >= data.count) break;
                }
            }
        }
    }

    return data;
}

// Save data to file (*.ini)
void rini_save(rini_data data, const char *file_name)
{
    FILE *rini_file = fopen(file_name, "wt");

    if (rini_file != NULL)
    {
        char valuestr[RINI_MAX_TEXT_SIZE + 2] = { 0 }; // Useful for text processing, adding quotation marks if required

        for (unsigned int i = 0; i < data.count; i++)
        {
            if ((data.entries[i].key[0] == '\0') && (data.entries[i].text[0] == '\0'))
            {
                if (data.entries[i].desc[0] == '\0') fprintf(rini_file, "\n");  // Empty line
                else if ((data.entries[i].desc[0] == ' ') && (data.entries[i].desc[1] == '\0')) // Empty comment line
                    fprintf(rini_file, "%c\n", RINI_LINE_COMMENT_DELIMITER);
                else fprintf(rini_file, "%c%s\n", RINI_LINE_COMMENT_DELIMITER, data.entries[i].desc); // Comment line
            }
            else
            {
                memset(valuestr, 0, RINI_MAX_TEXT_SIZE + 2);
#if RINI_USE_TEXT_QUOTATION_MARKS
                // Add quotation marks if required
                if (data.entries[i].is_text) snprintf(valuestr, RINI_MAX_TEXT_SIZE + 2, "%c%s%c", RINI_VALUE_QUOTATION_MARKS, data.entries[i].text, RINI_VALUE_QUOTATION_MARKS);
#else
                snprintf(valuestr, RINI_MAX_TEXT_SIZE + 2, "%s", data.entries[i].text);
#endif
                // Add description if required
                if (data.entries[i].desc[0] != '\0')
                {
                    fprintf(rini_file, "%-*s %c %-*s %c %s\n", RINI_KEY_SPACING, data.entries[i].key, RINI_VALUE_DELIMITER,
                        RINI_VALUE_SPACING, data.entries[i].is_text? valuestr : data.entries[i].text,
                        RINI_DESCRIPTION_DELIMITER, data.entries[i].desc);
                }
                else
                {
                    // No description required
                    fprintf(rini_file, "%-*s %c %s\n", RINI_KEY_SPACING, data.entries[i].key, RINI_VALUE_DELIMITER,
                        data.entries[i].is_text? valuestr : data.entries[i].text);
                }
            }
        }

        fclose(rini_file);
    }
}

// Save data to text buffer ('\0' EOL)
char *rini_save_to_memory(rini_data data)
{
    // Verify required data size is smaller than memory buffer size
    // NOTE: Adding 64 extra possible characters by entry line
    int requiredSize = 0;
    for (unsigned int i = 0; i < data.count; i++) requiredSize += ((int)strlen(data.entries[i].key) + (int)strlen(data.entries[i].text) + (int)strlen(data.entries[i].desc) + 64);
    if (requiredSize > RINI_MAX_TEXT_FILE_SIZE) RINI_LOG("WARNING: Required data.ini size is bigger than max supported memory size, increase RINI_MAX_TEXT_FILE_SIZE\n");

    // NOTE: Using a static buffer to avoid de-allocation requirement on user side
    static char text[RINI_MAX_TEXT_FILE_SIZE] = { 0 };
    memset(text, 0, RINI_MAX_TEXT_FILE_SIZE);
    int offset = 0;
    int expectedByteWritten = 0;

    char valuestr[RINI_MAX_TEXT_SIZE + 2] = { 0 }; // Useful for text processing, adding quotation marks if required

    for (unsigned int i = 0; i < data.count; i++)
    {
        if ((data.entries[i].key[0] == '\0') && (data.entries[i].text[0] == RINI_LINE_COMMENT_DELIMITER))
        {
            if (data.entries[i].desc[0] != '\0') expectedByteWritten = snprintf(text + offset, RINI_MAX_LINE_SIZE, "%c %s\n", RINI_LINE_COMMENT_DELIMITER, data.entries[i].desc);
            else expectedByteWritten = snprintf(text + offset, RINI_MAX_LINE_SIZE, "%c\n", RINI_LINE_COMMENT_DELIMITER);
        }
        else
        {
            memset(valuestr, 0, RINI_MAX_TEXT_SIZE + 2);
#if RINI_USE_TEXT_QUOTATION_MARKS
            // Add quotation marks if required
            if (data.entries[i].is_text) snprintf(valuestr, RINI_MAX_TEXT_SIZE + 2, "%c%s%c", RINI_VALUE_QUOTATION_MARKS, data.entries[i].text, RINI_VALUE_QUOTATION_MARKS);
#else
            snprintf(valuestr, RINI_MAX_TEXT_SIZE + 2, "%s", data.entries[i].text);
#endif
            // Add description if required
            if (data.entries[i].desc[0] != '\0')
            {
                expectedByteWritten = snprintf(text + offset, RINI_MAX_LINE_SIZE, "%-*s %c %-*s %c %s\n", RINI_KEY_SPACING, data.entries[i].key, RINI_VALUE_DELIMITER,
                        RINI_VALUE_SPACING, data.entries[i].is_text? valuestr : data.entries[i].text,
                        RINI_DESCRIPTION_DELIMITER, data.entries[i].desc);
            }
            else
            {
                // No description required
                int expectedByteWritten = snprintf(text + offset, RINI_MAX_LINE_SIZE, "%-*s %c %s\n", RINI_KEY_SPACING, data.entries[i].key, RINI_VALUE_DELIMITER,
                        data.entries[i].is_text? valuestr : data.entries[i].text);
            }
        }

        if (expectedByteWritten >= RINI_MAX_LINE_SIZE) offset += RINI_MAX_LINE_SIZE;
        else offset += expectedByteWritten;
    }

    return text;
}

// Unload data
void rini_unload(rini_data *data)
{
    RINI_FREE(data->entries);

    data->entries = NULL;
    data->count = 0;
    data->capacity = 0;
}

// Get value for provided key, returns 0 if not found or not valid
int rini_get_value(rini_data data, const char *key)
{
    int value = 0;

    for (unsigned int i = 0; i < data.count; i++)
    {
        if (strcmp(key, data.entries[i].key) == 0) // Key found
        {
            value = rini_text_to_int(data.entries[i].text);
            break;
        }
    }

    return value;
}

// Get value for provided key with default value fallback if not found or not valid
int rini_get_value_fallback(rini_data data, const char *key, int fallback)
{
    int value = fallback;

    for (unsigned int i = 0; i < data.count; i++)
    {
        if (strcmp(key, data.entries[i].key) == 0) // Key found
        {
            // TODO: Detect if conversion fails...
            value = rini_text_to_int(data.entries[i].text);
            break;
        }
    }

    return value;
}

// Get text for string id
const char *rini_get_value_text(rini_data data, const char *key)
{
    const char *text = NULL;

    for (unsigned int i = 0; i < data.count; i++)
    {
        if (strcmp(key, data.entries[i].key) == 0) // Key found
        {
            text = data.entries[i].text;
            break;
        }
    }

    return text;
}

// Get value text for provided key with fallback if not found or not valid
const char *rini_get_value_text_fallback(rini_data data, const char *key, const char *fallback)
{
    const char *text = fallback;

    for (unsigned int i = 0; i < data.count; i++)
    {
        if (strcmp(key, data.entries[i].key) == 0) // Key found
        {
            text = data.entries[i].text;
            break;
        }
    }

    return text;
}

// Get description for string id
const char *rini_get_value_description(rini_data data, const char *key)
{
    const char *desc = NULL;

    for (unsigned int i = 0; i < data.count; i++)
    {
        if (strcmp(key, data.entries[i].key) == 0) // Key found
        {
            desc = data.entries[i].desc;
            break;
        }
    }

    return desc;
}

// Set comment line
int rini_set_comment_line(rini_data *data, const char *comment)
{
    int result = -1;

    result = rini_set_value_text(data, NULL, NULL, comment);

    return result;
}

// Set value and description for existing key or create a new entry
int rini_set_value(rini_data *data, const char *key, int value, const char *desc)
{
    int result = -1;
    char value_text[RINI_MAX_TEXT_SIZE] = { 0 };

    snprintf(value_text, RINI_MAX_TEXT_SIZE, "%i", value);

    result = rini_set_value_text(data, key, value_text, desc);

    if (result == 0) // Value set!
    {
        // NOTE: Key may have already existed and updated, so
        // need to re-find it to update the flag manually
        for (unsigned int i = 0; i < data->count; i++)
        {
            if (strcmp(key, data->entries[i].key) == 0) // Key found
            {
                data->entries[i].is_text = false;
                break;
            }
        }
    }

    return result;
}

// Set value text and description for existing key or create a new entry
// NOTE: When setting a text value, if id does not exist, a new entry is automatically created
int rini_set_value_text(rini_data *data, const char *key, const char *text, const char *desc)
{
    int result = -1;

    if (key != NULL)
    {
        // Try to find key and update text and description
        for (unsigned int i = 0; i < data->count; i++)
        {
            if (strcmp(key, data->entries[i].key) == 0) // Key found
            {
                memset(data->entries[i].text, 0, RINI_MAX_TEXT_SIZE);
                if (text != NULL) memcpy(data->entries[i].text, text, strlen(text));

                if (desc != NULL)
                {
                    // NOTE: Update description only if new one provided,
                    // do not remove previous description
                    memset(data->entries[i].desc, 0, RINI_MAX_DESC_SIZE);
                    memcpy(data->entries[i].desc, desc, strlen(desc));
                }

                result = 0;
                break;
            }
        }
    }

    // Key not found, adding a new entry if possible
    if (result == -1)
    {
        if (data->count < data->capacity)
        {
            if ((key == NULL) && (text == NULL)) // Comment line
            {
                memset(data->entries[data->count].key, 0, RINI_MAX_KEY_SIZE);
                memset(data->entries[data->count].text, 0, RINI_MAX_TEXT_SIZE);

                if (desc != NULL)
                {
                    for (int i = 0; (i < RINI_MAX_DESC_SIZE) && (desc[i] != '\0'); i++) data->entries[data->count].desc[i] = desc[i];
                }
                else memset(data->entries[data->count].desc, 0, RINI_MAX_DESC_SIZE);
            }
            else
            {
                // NOTE: Doing a manual copy to avoid possible overflows on input data
                for (int i = 0; (i < RINI_MAX_KEY_SIZE) && (key[i] != '\0'); i++) data->entries[data->count].key[i] = key[i];
                for (int i = 0; (i < RINI_MAX_TEXT_SIZE) && (text[i] != '\0'); i++) data->entries[data->count].text[i] = text[i];
                if (desc != NULL) for (int i = 0; (i < RINI_MAX_DESC_SIZE) && (desc[i] != '\0'); i++) data->entries[data->count].desc[i] = desc[i];
            }

            data->entries[data->count].is_text = true;
            data->count++;
            result = 0;
        }
    }

    return result;
}

// Set value description for existing key
// WARNING: Key must exist to add description, if a description exists, it is updated
int rini_set_value_description(rini_data *data, const char *key, const char *desc)
{
    int result = 1;

    for (unsigned int i = 0; i < data->count; i++)
    {
        if (strcmp(key, data->entries[i].key) == 0) // Key found
        {
            memset(data->entries[i].desc, 0, RINI_MAX_DESC_SIZE);
            if (desc != NULL) memcpy(data->entries[i].desc, desc, strlen(desc));
            result = 0;
            break;
        }
    }

    return result;
}

//----------------------------------------------------------------------------------
// Module Internal Functions Declaration
//----------------------------------------------------------------------------------
// Get string id from a buffer line containing id-value pair
static int rini_read_key(const char *buffer, char *key)
{
    int len = 0;
    while ((buffer[len] != '\0') && (buffer[len] != ' ') && (buffer[len] != RINI_VALUE_DELIMITER)) len++;    // Skip keyentifier

    memcpy(key, buffer, len);

    return len;
}

// Get string-value from a buffer line containing id-value pair
static int rini_read_value_text(const char *buffer, char *text, char *desc, bool *is_text)
{
    char *buffer_ptr = (char *)buffer;

    // Expected line structure:
    // [key][spaces?][delimiter?][spaces?][quot-mark?][textValue][quot-mark?][spaces?][[;][#]description?]
    // NOTE: Processing requires skipping spaces, checking for delimiter (if required), skipping more spaces, and get text value

    while ((buffer_ptr[0] != '\0') && (buffer_ptr[0] != ' ')) buffer_ptr++; // Skip keyentifier

    while ((buffer_ptr[0] != '\0') && (buffer_ptr[0] == ' ')) buffer_ptr++; // Skip line spaces before text value or delimiter

#if defined(RINI_VALUE_DELIMITER)
    if (buffer_ptr[0] == RINI_VALUE_DELIMITER)
    {
        buffer_ptr++;       // Skip delimiter

        while ((buffer_ptr[0] != '\0') && (buffer_ptr[0] == ' ')) buffer_ptr++; // Skip line spaces before text value
    }
#endif

    // Now buffer_ptr should be pointing to the start of value

    int len = 0;
    while ((buffer_ptr[len] != '\0') &&
        (buffer_ptr[len] != '\r') &&
        (buffer_ptr[len] != '\n')) len++; // Get text-value and description length (to the end of line)

    // Now the length from text-value start to end of line is registered

    int value_len = len;
    int desc_pos = 0;
#if defined(RINI_DESCRIPTION_DELIMITER)
    // Scan text looking for text-value description (if used)
    for (; desc_pos < len; desc_pos++)
    {
        if (buffer_ptr[desc_pos] == RINI_DESCRIPTION_DELIMITER)
        {
            value_len = desc_pos - 1;
            while (buffer_ptr[value_len] == ' ') value_len--;

            value_len++;

            desc_pos++;   // Skip delimiter and following spaces
            while (buffer_ptr[desc_pos] == ' ') desc_pos++;
            break;
        }
    }
#endif

#if RINI_USE_TEXT_QUOTATION_MARKS
    // Remove starting quotation-mark from text (if being used)
    if (buffer_ptr[0] == RINI_VALUE_QUOTATION_MARKS)
    {
        buffer_ptr++; desc_pos--; len--; value_len--;

        // Remove ending quotation-mark from text (if being used)
        if (buffer_ptr[value_len - 1] == RINI_VALUE_QUOTATION_MARKS) { value_len--; }

        *is_text = true;
    }
#endif

    // Clear text buffers to be updated
    memset(text, 0, RINI_MAX_TEXT_SIZE);
    memset(desc, 0, RINI_MAX_DESC_SIZE);

    // Copy value-text and description to provided pointers
    memcpy(text, buffer_ptr, value_len);
    memcpy(desc, buffer_ptr + desc_pos, ((len - desc_pos) > (RINI_MAX_DESC_SIZE - 1))? (RINI_MAX_DESC_SIZE - 1) : (len - desc_pos));

    return len;
}

// Convert text to int value (if possible), same as atoi()
static int rini_text_to_int(const char *text)
{
    int value = 0;
    int sign = 1;

    if ((text[0] == '+') || (text[0] == '-'))
    {
        if (text[0] == '-') sign = -1;
        text++;
    }

    int i = 0;
    for (; ((text[i] >= '0') && (text[i] <= '9')); i++) value = value*10 + (int)(text[i] - '0');

    //if (strlen(text) != i) // Text starts with numbers but contains some text after that...

    return value*sign;
}