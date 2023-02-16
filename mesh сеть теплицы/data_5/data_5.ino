/*
 * Модуль для получения данных с датчика уровня воды
 * 
 * Распиновка для подключения:                                     
 *            PIN A0 - пин данных с датчика уровня воды
 *            
 * Идентификаторы и команды в сети:
 * 2 - включить реле увлажнителя воздуха
 * 3 - выключить реле увлажнителя воздуха
 * 4 - включить реле полива земли
 * 5 - выключить реле полива земли
 * 10 - форточка закрыта
 * 11 - форточка открыта на 30
 * 12 - форточка открыта на 45
 * 13 - форточка открыта на 90
 * 14 - форточка открыта на 110
 * от 50 до 200 - температура воздуха
 * от 200 до 400 - влажность воздуха
 * от 1000 до 3000 - влажность земли аналоговое значение
 * от 3000 до 5000 - уровень воды
 * 
 */
#include <Gyver433.h>                 // Подключаем библиотеку для работы с радиомодулем 433 МГц

#define SENSORPIN_A A0                //  Номер пина для подключения датчика уровня воды

Gyver433_TX<3> tx;                    //  Обьявляем обьект для работы с радиомодулем - указываем пин подключения
 
 // Переменные -----------------------------------
 int porog = 0;       // Переменная значения порога воды
 
 // Инициализация  -------------------------
void setup()
{            
    Serial.begin(9600);         // Включаем серийный порт для отладки   
}

void loop() 
{                            
     porog = analogRead(SENSORPIN_A) + 4000;  // Читаем аналоговое значение от датчика уровня воды   
     Serial.print(porog);// Отправляем в серийный порт для отладки             
     Serial.println();   // Переход на новую строку      
     char data[4];// Массив буфер фиксированного размера для отправки
     sprintf(data, "%d", porog);// Преобразуем значение
     tx.sendData(data);// Отправляем уровень воды
     delay(5000);// Пауза между отправками 5 секунд    
}
