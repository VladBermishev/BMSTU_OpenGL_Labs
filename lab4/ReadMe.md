## Основная теория

### Вещественный алгоритм Брезенхема

рассматривается случай построения отрезка в первом октанте (следовательно, задача сводится к выбору следующей точки отрезка из пары (xk+1, yk) и (xk+1, yk+1));

вводится понятие ошибки – расстояния от фактической точки отрезка до точки растра (xk+1, yk) при x = xk+1;

инициализация:
     
    De = m = Dy / Dx
    e = -1/2 (чтобы анализировать только знак)
    x = x0, y = y0

на каждой итерации алгоритма:

    e += De,
    x += 1,
    y += 1, e -=1, если e >= 0

недостаток: использование вещественной арифметики

![4](https://user-images.githubusercontent.com/34008816/167489868-738c03c8-475f-41aa-9901-eda59ae7a5f0.png)

### Целочисленный алгоритм Брезенхема

e’ = 2eDx (так как важен только знак ошибки)

инициализация:
      
      De = 2Dye 0 = - Dx
      x = x0, y = y0
      
на каждой итерации алгоритма:

    e += De
    x += 1,
    y += 1, e -= 2Dx, если e  >= 0
    
![image](https://user-images.githubusercontent.com/34008816/167490988-5a3b0fad-229d-479f-a480-c075c01a1226.png)

### Алгоритм заполнения многоугольника по ребрам

для каждой строки сканирования инвертируются все пиксели справа от точки пересечения данной строки сканирования с ребром многоугольника

порядок обработки ребер многоугольника не важен

каждый пиксель может обрабатываться многократно

![5](https://user-images.githubusercontent.com/34008816/167491213-ee6d7ad8-5f75-4045-b201-88405fc103bb.png)

### Фильтрация

фильтрация представляет собой свертку (convolution) сигнала (изображения) с ядром свертки (функцией фильтра) – усреднение сигнала в некоторой области

примеры фильтров:
 1. размытие (простейшее усреднение, константное, гауссово)
 2. повышение четкости
 3. нахождение границ
 4. тиснение 
 5. медианный фильтр

![6](https://user-images.githubusercontent.com/34008816/167491522-1ac9f81a-c901-401b-bf28-c53d2579eecb.png)

### Постфильтрация

усреднение характеристик пикселя:
 1. равномерное
 2. взвешенное
 
 ![7](https://user-images.githubusercontent.com/34008816/167491670-0a905199-2d63-48dd-bf3c-e9cce39c9d6b.png)

##
### Построение отрезков целочисленным алгоритмом Брезенхема

![8](https://user-images.githubusercontent.com/34008816/167491885-26586599-6ce1-479b-9133-b356a99b9921.png)

### Отображение радиуса точек для упрощенного ввода отрезков

![9](https://user-images.githubusercontent.com/34008816/167492037-98be2151-ca6e-43c2-99e0-da5186210c2a.png)

### Заполнение многоугольника по ребрам

![10](https://user-images.githubusercontent.com/34008816/167492137-b3a80d19-cfef-4ad4-933f-774937119914.png)

### Постфильтрация с взвешенным усреднением области 3х3

![11](https://user-images.githubusercontent.com/34008816/167492146-c5865957-b5d1-4615-989e-948d6d130385.png)

### Изменение размера окна

![12](https://user-images.githubusercontent.com/34008816/167492178-031eba03-c8b8-47db-9bb1-2a584a14b2bb.png)

## Заключение

По мере выполнения лабораторной работы был реализован целочисленный алгоритм Брезенхема, для отображения отрезков

Также для упрощения ввода отрезков были реализованы радиусы точек, при попаданий очередного нажатия в радиус точки новая точка будет эквивалентна уже существующей

Далее был реализован алгоритм заполнения многоугольника по ребрам

Следующим был реализован алгоритм постфильтрация с взвешенным усреднением области 3х3

В последнюю очередь была введена возможность изменения размеров окна
