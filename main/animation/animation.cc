/*
 * @Descripttion: 
 * @Author: Xvsenfeng helloworldjiao@163.com
 * @LastEditors: Xvsenfeng helloworldjiao@163.com
 * Copyright (c) 2025 by helloworldjiao@163.com, All Rights Reserved. 
 */
#include "animation.h"
#include "lvgl.h"
#include "board.h"
#include "display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <type_traits>
extern const lv_image_dsc_t embarrass1;
extern const lv_image_dsc_t embarrass2;
extern const lv_image_dsc_t embarrass3;
extern const lv_image_dsc_t fire1;
extern const lv_image_dsc_t fire2;
extern const lv_image_dsc_t fire3;
extern const lv_image_dsc_t fire4;
extern const lv_image_dsc_t inspiration1;
extern const lv_image_dsc_t inspiration2;
extern const lv_image_dsc_t inspiration3;
extern const lv_image_dsc_t inspiration4;
extern const lv_image_dsc_t normal1;
extern const lv_image_dsc_t normal2;
extern const lv_image_dsc_t normal3;
extern const lv_image_dsc_t question1;
extern const lv_image_dsc_t question2;
extern const lv_image_dsc_t question3;
extern const lv_image_dsc_t question4;
extern const lv_image_dsc_t shy1;
extern const lv_image_dsc_t shy2;
extern const lv_image_dsc_t sleep1;
extern const lv_image_dsc_t sleep2;
extern const lv_image_dsc_t sleep3;
extern const lv_image_dsc_t sleep4;
extern const lv_image_dsc_t happy1;
extern const lv_image_dsc_t happy2;
extern const lv_image_dsc_t happy3;
extern const lv_image_dsc_t happy4;

const lv_image_dsc_t *embarrass_i[3] = {
    &embarrass1,
    &embarrass2,
    &embarrass3
};

const lv_image_dsc_t *fire_i[4] = {
    &fire1,
    &fire2,
    &fire3,
    &fire4
};

const lv_image_dsc_t *inspiration_i[4] = {
    &inspiration1,
    &inspiration2,
    &inspiration3,
    &inspiration4
};

const lv_image_dsc_t *normal_i[3] = {
    &normal1,
    &normal2,
    &normal3
};

const lv_image_dsc_t *question_i[4] = {
    &question1,
    &question2,
    &question3,
    &question4
};

const lv_image_dsc_t *shy_i[2] = {
    &shy1,
    &shy2
};

const lv_image_dsc_t *sleep_i[4] = {
    &sleep1,
    &sleep2,
    &sleep3,
    &sleep4
};
const lv_image_dsc_t *happy_i[4] = {
    &happy1,
    &happy2,
    &happy3,
    &happy4
};

Animation_t static_normal = {
    .imges = normal_i,
    .animations = (int[]){0},
    .len = 1
};
Animation_t animation_embressed = {
    .imges = embarrass_i,
    .animations = (int[]){0, 1, 2},
    .len = 3
};
Animation_t animation_fire = {
    .imges = fire_i,
    .animations = (int[]){0, 1, 2, 3},
    .len = 4
};
Animation_t animation_inspiration = {
    .imges = inspiration_i,
    .animations = (int[]){0, 1, 2, 3},
    .len = 4
};
Animation_t animation_normal = {
    .imges = normal_i,
    .animations = (int[]){0, 1, 2},
    .len = 3
};
Animation_t animation_question = {
    .imges = question_i,
    .animations = (int[]){0, 1, 2, 3},
    .len = 4
};
Animation_t animation_shy = {
    .imges = shy_i,
    .animations = (int[]){0, 1},
    .len = 2
};
Animation_t animation_sleep = {
    .imges = sleep_i,
    .animations = (int[]){0, 1, 2, 3},
    .len = 4
};
Animation_t animation_happy = {
    .imges = happy_i,
    .animations = (int[]){0, 1, 2, 3},
    .len = 4
};

Animation_t *animations[] = {
    &static_normal,
    &animation_embressed,
    &animation_fire,
    &animation_inspiration,
    &animation_normal,
    &animation_question,
    &animation_shy,
    &animation_sleep,
    &animation_happy
};

static int now_animation = 0;
int pos = 0;
TaskHandle_t animation_task_handle = nullptr;

void plat_animation_task(void *arg){
    auto display = Board::GetInstance().GetDisplay();
    while(1){
        ESP_LOGD("plat_animation_task", "now_animation: %d, pos: %d", now_animation, pos);
        pos++;
        if(pos >= animations[now_animation]->len){
            pos = 0;
        }
        display->SetEmotionImg(animations[now_animation]->imges[animations[now_animation]->animations[pos]]);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
}

void animation_set_now_animation(int animation){
    if(animation_task_handle == nullptr){
        xTaskCreate(plat_animation_task, "plat_animation_task", 2048, nullptr, 4, &animation_task_handle);
    }
    if(animation < 0 || animation >= ANIMATION_NUM){
        return;
    }
    ESP_LOGI("animation_set_now_animation", "Set now animation: %d", animation);
    now_animation = animation;
    pos = 0;
}
