#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list_node_t {
    void* data;
    struct linked_list_node_t* next;
} linked_list_node_t;

typedef struct song_t {
    const char* name;
    float duration;
} song_t;

linked_list_node_t** array_of_playlist_ptrs = NULL;

void create_array_of_linked_list_ptrs(linked_list_node_t*** destination, int size) {
    *destination = (linked_list_node_t**)(malloc(size * sizeof(linked_list_node_t*)));
    for (int i = 0; i < size; i++) {
        (*destination)[i] = NULL;
    }
}

void get_element_of_array_of_linked_list_ptrs(linked_list_node_t** array, int index, linked_list_node_t*** destination) {
    *destination = &(array[index]);
}

void set_element_of_array_of_linked_list_ptrs(linked_list_node_t** array, int index, linked_list_node_t* head) {
    array[index] = head;
}

void destroy_array_of_linked_list_ptrs(linked_list_node_t** array) {
    free(array);
}

void resize_array_of_linked_list_ptrs(linked_list_node_t*** destination, linked_list_node_t** array, int size, int new_size) {
    *destination = (linked_list_node_t**)(realloc(array, new_size * sizeof(linked_list_node_t*)));
    for (int i = size; i < new_size; i++) {
        (*destination)[i] = NULL;
    }
}

void create_link_list(linked_list_node_t** destination) {
    *destination = NULL;
}

void destroy_linked_list(linked_list_node_t* head) {
    while (head != NULL) {
        linked_list_node_t* temp = head;
        head = head->next;
        free(temp);
    }
}

void add_to_linked_list(linked_list_node_t** head, const void* data) {
    linked_list_node_t* new_node = (linked_list_node_t*)(malloc(sizeof(linked_list_node_t)));
    new_node->data = (void*)data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        linked_list_node_t* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void remove_from_linked_list(linked_list_node_t*** destination, linked_list_node_t** head, const void* data) {
    linked_list_node_t* current = *head;
    linked_list_node_t* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous == NULL) {
            *head = current->next;
        } else {
            previous->next = current->next;
        }
        *destination = &(current->data);
        free(current);
    } else {
        *destination = NULL;
    }
}

void create_song(song_t* destination, const char* name, float duration) {
    destination->name = name;
    destination->duration = duration;
}

int main(void) {
    int playlist_size = 5;
    create_array_of_linked_list_ptrs(&array_of_playlist_ptrs, playlist_size);

    for (int i = 0; i < playlist_size; i++) {
        create_link_list(&(array_of_playlist_ptrs[i]));
    }

    set_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, 0, array_of_playlist_ptrs[0]);

    resize_array_of_linked_list_ptrs(&array_of_playlist_ptrs, array_of_playlist_ptrs, playlist_size, 10);

    for (int i = playlist_size; i < 10; i++) {
        create_link_list(&(array_of_playlist_ptrs[i]));
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            song_t* song = (song_t*)(malloc(sizeof(song_t)));
            create_song(song, "SongName", (j+1)*1.36);
            add_to_linked_list(&(array_of_playlist_ptrs[i]), song);
        }
    }

    for (int i = 0; i < 10; i++) {
        linked_list_node_t** removed_song_data = NULL;
        get_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, i, &removed_song_data);
        remove_from_linked_list(&removed_song_data, &(array_of_playlist_ptrs[i]), (array_of_playlist_ptrs[i])->next->data);
    }

    for (int i = 0; i < 10; i++) {
        linked_list_node_t* current = array_of_playlist_ptrs[i];
        printf("Playlist %d:\n", i + 1);
        while (current != NULL) {
            song_t* song = (song_t*)(current->data);
            printf("  Song: %s, Duration: %.2f\n", song->name, song->duration);
            current = current->next;
        }
    }

    for (int i = 0; i < 10; i++) {
        destroy_linked_list(array_of_playlist_ptrs[i]);
    }

    destroy_array_of_linked_list_ptrs(array_of_playlist_ptrs);

    return 0;
}
