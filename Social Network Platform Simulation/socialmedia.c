#include "socialmedia.h"

#include <stdlib.h>

Database db;
Cache userCache;
Cache postCache;

void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() {
    printf("UserCache:\n");
    Node *current = userCache.head;
    while (current != NULL) {
        printUser((User *)current->data);
        current = current->next;
    }
}

void printPostCache() {
    printf("PostCache:\n");
    Node *current = postCache.tail;
    while (current != NULL) {
        printPost((Post *)current->data);
        current = current->prev;
    }
}


Node *createNode(void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void appendToCache(Cache *cache, void *data) {
    if (cache->size == cache->capacity) {
        removeLast(cache);
    }
    Node *newNode = createNode(data);
    newNode->next = cache->head;
    if (cache->head != NULL) {
        cache->head->prev = newNode;
    }
    cache->head = newNode;
    if (cache->tail == NULL) {
        cache->tail = newNode;
    }
    cache->size++;
}


void moveToFront(Cache *cache, Node *node) {
    if (cache->head == node) {
        return;
    }

    // Remove node from its current position
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (cache->tail == node) {
        cache->tail = node->prev;
    }

    // Move node to the front
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head != NULL) {
        cache->head->prev = node;
    }
    cache->head = node;
    if (cache->tail == NULL) {
        cache->tail = node;
    }
}


void removeLast(Cache *cache) {
    if (cache->tail == NULL) {
        return;
    }
    Node *oldTail = cache->tail;
    if (cache->tail->prev != NULL) {
        cache->tail->prev->next = NULL;
    } else {
        cache->head = NULL;
    }
    cache->tail = cache->tail->prev;
    free(oldTail);
    cache->size--;
}


User *fetchUser(int userId) {
    Node *current = userCache.head;
    while (current != NULL) {
        User *user = (User *)current->data;
        if (user->userId == userId) {
            moveToFront(&userCache, current);
            return user;
        }
        current = current->next;
    }
    // User not found in cache, fetch from database
    User *user = &db.users[userId];
    appendToCache(&userCache, user);
    return user;
}

Post *fetchPost(int postId) {
    Node *current = postCache.head;
    while (current != NULL) {
        Post *post = (Post *)current->data;
        if (post->postId == postId) {
            moveToFront(&postCache, current);
            return post;
        }
        current = current->next;
    }
    // Post not found in cache, fetch from database
    Post *post = &db.posts[postId];
    appendToCache(&postCache, post);
    return post;
}

void followUser(int followerId, int followedId) {
    User *follower = fetchUser(followerId);
    User *followed = fetchUser(followedId);
    
    Node *newFollowerNode = createNode(follower);
    if (followed->followers_tail != NULL) {
        followed->followers_tail->next = newFollowerNode;
        newFollowerNode->prev = followed->followers_tail;
    } else {
        followed->followers_head = newFollowerNode;
    }
    followed->followers_tail = newFollowerNode;
    
    followed->numOfFollowers++;
    follower->numOfFollowing++;
}


void likePost(int userId, int postId) {
    User *user = fetchUser(userId);
    Post *post = fetchPost(postId);

    user->liked++;
    post->likes++;
}

//void printFollowersInReverse() {
  //printf("Followers of all users in UserCache in reverse:\n");
  ///* For each user in the UserCache... */
  //printf("Followers of user with id %d in reverse:\n", /* TODO */);
//}

void printFollowersInReverse() {
    printf("Followers of all users in UserCache in reverse:\n");
    Node *current = userCache.tail;
    while (current != NULL) {
        User *user = (User *)current->data;
        printf("Followers of user with id %d in reverse:\n", user->userId);
        Node *followerCurrent = user->followers_tail;
        while (followerCurrent != NULL) {
            printUser((User *)followerCurrent->data);
            followerCurrent = followerCurrent->prev;
        }
        current = current->prev;
    }
}


void freeLinkedList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

