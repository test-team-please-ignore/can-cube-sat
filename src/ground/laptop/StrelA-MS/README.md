# StrelA MS
## Общее
СтрелА МС (StrelA MS) - программное обеспечение, созданное с целью отображения различного рода телеметрии в реальном времени и записи ее в лог-файлы для дальнейшего воспроизведения.

Для работы программы необходим python 3.6 и выше.

## Установка
* Скачайте репозиторий с программой
* Установите библиотеки из requirements.txt
* Соберите MAVLink, включив в него диалект its

## Настройка
Для работы приложению необходим файл с настройками. По умолчанию используется файл StrelA_MS.ini, но пользователь может использовать свой, записав в переменную окружения STRELA_MS_CONFIG путь до желаемого файла.

Пример:

`set "STRELA_MS_CONFIG=./config_templates/StrelA_MS_EXAMPLE.ini"`

Стоит учитывать, что файл с настройками может редактироваться не только пользователем, но и самим приложением.

Шаблоны Файлов с настройками лежат в папке config_templates.

## Запуск
Запустите main.py при помощи команды:
* Для Windows

    `python main.py`

* Для Linux

    `python3 main.py`

## Редактирование файла с настройками
Во время работы программы все входящие пакеты преобразуются во внутренние пакеты, имеющие уникальное имя, по которому виджеты и их компоненты находят необходимые им данные и которое необходимо прописать в соответствующих полях настроек.

Каждая настройка имеет вид ключ=значение, причем настройки можно группировать, добавляя в начало ключей единой для всей группы префикса, отделенный от остальной части ключа обратным слешем.

Пример:

`DataWidget\Data_table\is_on=2`

Если значение - массив, то его элементы должны быть отделены запятой (иногда необходима подстановка дополнительной запятой в конец массива)

Каждый новый график или блок в таблице добавляется путем создания в нужном разделе нового раздела с уникальным именем. 

Пример добавления двух графиков:

```
GraphWidget\Graph\PLOT_1\colour=r, 
GraphWidget\Graph\PLOT_1\is_on=2
GraphWidget\Graph\PLOT_1\max_data_length=100
GraphWidget\Graph\PLOT_1\packet_name=0, PACK_1, 1
GraphWidget\Graph\PLOT_1\position=0, 0, 1, 1
GraphWidget\Graph\PLOT_2\colour=r, 
GraphWidget\Graph\PLOT_2\is_on=2
GraphWidget\Graph\PLOT_2\max_data_length=100
GraphWidget\Graph\PLOT_2\packet_name=0, PACK_2, 1
GraphWidget\Graph\PLOT_2\position=0, 1, 1, 1
```

В файле с настройками присутствуют несколько глобальных разделов, помеченных квадратными скобками (пример `[CentralWidget]`)

### CentralWidget
Раздел, содержащий настройки для базовых виджетов. На данный момент существует 4 таких виджета:

#### DataWidget
"Виджет-табличка", содержащий данные из внутренних пакетов в виде таблицы, первый столбец которого - имя блока, второй - имя параметра и третий - значение параметра.

Настройки виджета:

| Название         | Описание                                                                   | Возможные значения              | Примечания |
| ---------------- | -------------------------------------------------------------------------- | ------------------------------- | ---------- |
| background_color | цвет фона                                                                  | цвет в формате RGB              |            |
| colors           | цвета ячеек при выходе за допустимый диапазон и истечении времени ожидания | три цвета в формате RGB         |            |
| is_on            | ВКЛ/ВЫКЛ виджет                                                            | 2 - ВКЛ, 0 - ВЫКЛ               |            |
| position         | позиция крайней занимаемой клетки сетки и размер виджета                   | строка, столбец, высота, ширина |            |

Пример:

```
DataWidget\background_color=#888888
DataWidget\colors=#0000FF, #FF0000, #FFFF00
DataWidget\is_on=2
DataWidget\position=1, 1, 1, 1
```

Состоит из двух идейно разных разделов:
##### Time_table 
Раздел, содержащий данные о времени подсистем.

Настройки раздела:

| Название  | Описание        | Возможные значения | Примечания |
| --------- | --------------- | ------------------ | ---------- |
| is_on     | ВКЛ/ВЫКЛ раздел | 2 - ВКЛ, 0 - ВЫКЛ  |            |

Каждая новая система добавляется за счет создания нового раздела, содержащего следущие настройки:

| Название    | Описание                                   | Возможные значения | Примечания                         |
| ----------- | ------------------------------------------ | ------------------ | ---------------------------------- |
| is_on       | ВКЛ/ВЫКЛ раздел                            | 2 - ВКЛ, 0 - ВЫКЛ  |                                    |
| name        | имя параметра                              | строка             |                                    |
| packet_name | массив имен пакетов, относящихся к системе | массив строк       | в конце массива необходима запятая |
| time_limit  | максимальное время ожидания пакета         | время в секундах   |                                    |

Пример:

```
DataWidget\Time_table\SUBSYS_1\is_on=2
DataWidget\Time_table\SUBSYS_1\name=subsystem 1 name
DataWidget\Time_table\SUBSYS_1\packet_name=SUBSYS_1_PACK_1, SUBSYS_1_PACK_2,
DataWidget\Time_table\SUBSYS_1\time_limit=1
DataWidget\Time_table\SUBSYS_2\is_on=2
DataWidget\Time_table\SUBSYS_2\name=subsystem 2 name
DataWidget\Time_table\SUBSYS_2\packet_name=SUBSYS_2_PACK_1,
DataWidget\Time_table\SUBSYS_2\time_limit=1
DataWidget\Time_table\is_on=2
```
##### Data_table 
Раздел, содержащий данные из внутренних пакетов.

Настройки раздела:

| Название  | Описание        | Возможные значения | Примечания |
| --------- | --------------- | ------------------ | ---------- |
| is_on     | ВКЛ/ВЫКЛ раздел | 2 - ВКЛ, 0 - ВЫКЛ  |            |

Каждая новый пакет добавляется за счет создания нового раздела, содержащего следущие настройки:

| Название    | Описание                                   | Возможные значения | Примечания                         |
| ----------- | ------------------------------------------ | ------------------ | ---------------------------------- |
| is_on       | ВКЛ/ВЫКЛ раздел                            | 2 - ВКЛ, 0 - ВЫКЛ  |                                    |
| name        | имена параметров                           | массив строк       | в конце массива необходима запятая |
| packet_name | имя пакета                                 | строка             |                                    |
| range       | массив диапазонов значений параметров      | массив чисел       | (min_1, max_1, min_2, max_2 ...)   |
| time_limit  | максимальное время ожидания пакета         | время в секундах   |                                    |

Пример:

```
DataWidget\Data_table\is_on=2
DataWidget\Data_table\SUBSYS_1_DATA\is_on=2
DataWidget\Data_table\SUBSYS_1_DATA\name=field 1 name, field 2 name,
DataWidget\Data_table\SUBSYS_1_DATA\packet_name=SUBSYS_1_DATA_PACK
DataWidget\Data_table\SUBSYS_1_DATA\range=0, 1, 0, 1
DataWidget\Data_table\SUBSYS_1_DATA\time_limit=1
DataWidget\Data_table\SUBSYS_2_DATA\is_on=2
DataWidget\Data_table\SUBSYS_2_DATA\name=field 1 name, 
DataWidget\Data_table\SUBSYS_2_DATA\packet_name=SUBSYS_2_DATA_PACK
DataWidget\Data_table\SUBSYS_2_DATA\range=0, 1, 0, 1
DataWidget\Data_table\SUBSYS_2_DATA\time_limit=1
```
##### Packet_table 
Раздел, содержащий данные о количестве обработанных пакетов.

Настройки раздела:

| Название  | Описание        | Возможные значения | Примечания |
| --------- | --------------- | ------------------ | ---------- |
| is_on     | ВКЛ/ВЫКЛ раздел | 2 - ВКЛ, 0 - ВЫКЛ  |            |

Каждая новый пакет добавляется за счет создания нового раздела, содержащего следущие настройки:

| Название    | Описание                                   | Возможные значения | Примечания |
| ----------- | ------------------------------------------ | ------------------ | ---------- |
| is_on       | ВКЛ/ВЫКЛ раздел                            | 2 - ВКЛ, 0 - ВЫКЛ  |            |
| name        | имя пакета при отображении                 | строка             |            |
| packet_name | имя пакета                                 | строка             |            |

Пример:

```
DataWidget\Packet_table\SUBSYS_P1\is_on=2
DataWidget\Packet_table\SUBSYS_P1\name=subsystem 1 packet 1 name
DataWidget\Packet_table\SUBSYS_P1\packet_name=SUBSYS_1_PACK_1
DataWidget\Packet_table\SUBSYS_P2\is_on=2
DataWidget\Packet_table\SUBSYS_P2\name=subsystem 1 packet 2 name
DataWidget\Packet_table\SUBSYS_P2\packet_name=SUBSYS_1_PACK_2
DataWidget\Packet_table\is_on=2
```
#### GraphWidget
"Виджет с графиками", содержащий данные из внутренних пакетов в виде графиков.

Настройки виджета:

| Название | Описание                                                 | Возможные значения              | Примечания |
| -------- | -------------------------------------------------------- | ------------------------------- | ---------- |
| is_on    | ВКЛ/ВЫКЛ виджет                                          | 2 - ВКЛ, 0 - ВЫКЛ               |            |
| position | позиция крайней занимаемой клетки сетки и размер виджета | строка, столбец, высота, ширина |            |
| units    | единицы измерения для оси времени                        | строка                          |            |

Пример:

```
GraphWidget\is_on=2
GraphWidget\position=1, 0, 1, 1
GraphWidget\time_units=s
```
Каждый новый график добавляется за счет создания нового раздела, содержащего следущие настройки:

| Название        | Описание                                         | Возможные значения              | Примечания                         |
| --------------- | ------------------------------------------------ | ------------------------------- | ---------------------------------- |
| colour          | массив цветов линий                              | цвета в формате RGB             | в конце массива необходима запятая |
| is_on           | ВКЛ/ВЫКЛ раздел                                  | 2 - ВКЛ, 0 - ВЫКЛ               |                                    |
| max_data_length | максимальная длинна отображаемого массива        | число больше нуля               |                                    |
| packet_name     | массив имен пакетов и диапазона номеров линий    | строки + диапазон (см. range()) | (начало, имя пакета, конец, ...)   |
| position        | позиция крайней занимаемой клетки сетки и размер | строка, столбец, высота, ширина |                                    |
| units           | единицы измерения                                | строка                          |                                    |

И подраздел, содержащий настройки легенды

| Название        | Описание          | Возможные значения | Примечания                         |
| --------------- | ----------------- | ------------------ | ---------------------------------- |
| is_on           | ВКЛ/ВЫКЛ легенду  | 2 - ВКЛ, 0 - ВЫКЛ  |                                    |
| name            | подписи для линий | массив строк       | в конце массива необходима запятая |

Пример:

```
GraphWidget\Graph\PLOT_1\colour=r, 
GraphWidget\Graph\PLOT_1\is_on=2
GraphWidget\Graph\PLOT_1\max_data_length=100
GraphWidget\Graph\PLOT_1\packet_name=0, PACK_1, 1
GraphWidget\Graph\PLOT_1\position=0, 0, 1, 1
GraphWidget\Graph\PLOT_1\Legend\is_on=2
GraphWidget\Graph\PLOT_1\Legend\name=PACK_1, 
GraphWidget\Graph\PLOT_1\units=units
GraphWidget\Graph\PLOT_2\colour=r, 
GraphWidget\Graph\PLOT_2\is_on=2
GraphWidget\Graph\PLOT_2\max_data_length=100
GraphWidget\Graph\PLOT_2\packet_name=0, PACK_2, 1
GraphWidget\Graph\PLOT_2\position=0, 1, 1, 1
GraphWidget\Graph\PLOT_2\Legend\is_on=2
GraphWidget\Graph\PLOT_2\Legend\name=PACK_2, 
GraphWidget\Graph\PLOT_2\units=units
```

#### MapWidget
"Виджет с картой", содержащий данные о географическом положении в виде карты.

Настройки виджета:

| Название         | Описание                                                 | Возможные значения              | Примечания |
| ---------------- | -------------------------------------------------------- | ------------------------------- | ---------- |
| center           | Центр по умолчанию                                       | lat, lon                        |            |
| follow           | ВКЛ/ВЫКЛ следование за маркером                         | строка, столбец, высота, ширина |            |
| is_on            | ВКЛ/ВЫКЛ виджет                                          | 2 - ВКЛ, 0 - ВЫКЛ               |            |
| max_data_length  | максимальная длинна отображаемого массива                | число больше нуля               |            |
| packet_name      | имя пакета с координатами                                | строка                          |            |
| position         | позиция крайней занимаемой клетки сетки и размер виджета | строка, столбец, высота, ширина |            |
| zoom             | масштаб                                                  | число от 0 до 18                |            |

Пример:

```
MapWidget\center=55.9, 37.8
MapWidget\follow=2
MapWidget\is_on=2
MapWidget\max_data_length=0
MapWidget\packet_name=MAP
MapWidget\position=0, 1, 1, 1
MapWidget\zoom=11
```
#### ModelWidget
"Виджет с моделькой", содержащий данные об ориентации в виде модельки.

Настройки виджета:

| Название         | Описание                                                 | Возможные значения              | Примечания |
| ---------------- | -------------------------------------------------------- | ------------------------------- | ---------- |
| background_color | цвет фона                                                | цвет в формате RGB              |            |
| is_on            | ВКЛ/ВЫКЛ виджет                                          | 2 - ВКЛ, 0 - ВЫКЛ               |            |
| packet_name      | имя пакета с кватернионом                                | строка                          |            |
| position         | позиция крайней занимаемой клетки сетки и размер виджета | строка, столбец, высота, ширина |            |

Пример:

```
ModelWidget\background_color=#323232
ModelWidget\is_on=2
ModelWidget\packet_name=11_0_SINS_MODEL
ModelWidget\position=0, 0, 1, 1
```

Состоит из нескольких разделов:
##### Axis 
Раздел, отвечающий за отрисовку стандартных осей.

Настройки раздела:

| Название  | Описание        | Возможные значения | Примечания         |
| --------- | --------------- | ------------------ | ------------------ |
| is_on     | ВКЛ/ВЫКЛ раздел | 2 - ВКЛ, 0 - ВЫКЛ  |                    |
| scale     | размер          | три числа          | (по x, по y, по z) |
| translate | положение       | три числа          | (x, y, z)          |

Пример:

```
ModelWidget\Axis\is_on=2
ModelWidget\Axis\scale=6.5, 6.5, 7
ModelWidget\Axis\translate=0, 0, -5
```
##### Camera 
Раздел, отвечающий за положение камеры.

Настройки раздела:

| Название  | Описание                       | Возможные значения | Примечания |
| --------- | ------------------------------ | ------------------ | ---------- |
| azimuth   | горизонтальный угол            | угол в градусах    |            |
| distance  | расстояние от центра до камеры | число              |            |
| elevation | вертикальный угол              | угол в градусах    |            |
| pan       | положение центра               | три числа          | (x, y, z)  |

Пример:

```
ModelWidget\Camera\azimuth=0
ModelWidget\Camera\distance=470
ModelWidget\Camera\elevation=35
ModelWidget\Camera\pan=0, 0, 30
```

##### Grid 
Раздел, отвечающий за отрисовку сетки.

Настройки раздела:

| Название  | Описание        | Возможные значения | Примечания         |
| --------- | --------------- | ------------------ | ------------------ |
| is_on     | ВКЛ/ВЫКЛ раздел | 2 - ВКЛ, 0 - ВЫКЛ  |                    |
| scale     | размер          | три числа          | (по x, по y, по z) |
| translate | положение       | три числа          | (x, y, z)          |

Пример:

```
ModelWidget\Grid\is_on=2
ModelWidget\Grid\scale=3, 3, 3
ModelWidget\Grid\translate=0, 0, -10
```

##### Mesh 
Раздел, отвечающий за отрисовку модели.

Настройки раздела:

| Название        | Описание                  | Возможные значения | Примечания                           |
| --------------- | ------------------------- | ------------------ | ------------------------------------ |
| compute_normals | учет нормалей             | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| draw_edges      | отрисовка ребер           | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| draw_faces      | отрисовка полигонов       | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| path            | Путь до файла с моделькой | три числа          |                                      |
| shader          | название шейдера          | строка             | подходят только шейдеры из pyqtgraph |
| smooth          | сглаживание               | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |

Пример:

```
ModelWidget\Mesh\compute_normals=2
ModelWidget\Mesh\draw_edges=0
ModelWidget\Mesh\draw_faces=2
ModelWidget\Mesh\path=./source/models/CanCubeSat-for-GKS.stl
ModelWidget\Mesh\shader=edgeHilight
ModelWidget\Mesh\smooth=0
```
Содержит раздел:

###### Colors
Раздел отвечает за цветовую схему модели

Настройки раздела:

| Название | Описание                        | Возможные значения | Примечания                                     |
| -------- | ------------------------------- | ------------------ | ---------------------------------------------- |
| is_on    | ВКЛ/ВЫКЛ раздел                 | 2 - ВКЛ, 0 - ВЫКЛ  |                                                |
| path     | Путь до файла с массивом цветов | строка             | цвет каждого полигона представлен в виде ">4f" |

Пример:

```
ModelWidget\Mesh\Colors\is_on=2
ModelWidget\Mesh\Colors\path=./source/models/CanCubeSat-for-GKS_color.mfcl
```

##### Scene 
Раздел, отвечающий за отрисовку окружения модели в виде некоторой статичной модели.

Настройки раздела:

| Название        | Описание                  | Возможные значения | Примечания                           |
| --------------- | ------------------------- | ------------------ | ------------------------------------ |
| compute_normals | учет нормалей             | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| draw_edges      | отрисовка ребер           | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| draw_faces      | отрисовка полигонов       | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| is_on           | ВКЛ/ВЫКЛ раздел           | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| path            | Путь до файла с моделькой | строка             |                                      |
| shader          | название шейдера          | строка             | подходят только шейдеры из pyqtgraph |
| smooth          | сглаживание               | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |

Пример:

```
ModelWidget\Scene\compute_normals=2
ModelWidget\Scene\draw_edges=0
ModelWidget\Scene\draw_faces=2
ModelWidget\Scene\is_on=2
ModelWidget\Scene\path=./source/models/axis.stl
ModelWidget\Scene\shader=balloon
ModelWidget\Scene\smooth=0
```
Содержит раздел:

###### Colors
Раздел отвечает за цветовую схему сцены

Настройки раздела:

| Название | Описание                        | Возможные значения | Примечания                                     |
| -------- | ------------------------------- | ------------------ | ---------------------------------------------- |
| is_on    | ВКЛ/ВЫКЛ раздел                 | 2 - ВКЛ, 0 - ВЫКЛ  |                                                |
| path     | Путь до файла с массивом цветов | строка             | цвет каждого полигона представлен в виде ">4f" |

Пример:

```
ModelWidget\Scene\Colors\is_on=2
ModelWidget\Scene\Colors\path=./source/models/axis.mfcl
```

### CurrentValues
Раздел, содержащий текущие внутренние настройки. Не подлежит изменению.

### DefaultValues
Раздел, содержащий стандартные значения внутренних настроек. Для изменения не предполагается.

### CentralWidget
Раздел, содержащий настройки главного окна и приложения вцелом.

Настройки главного окна и приложения:

| Название    | Описание                         | Возможные значения | Примечания |
| ----------- | -------------------------------- | ------------------ | ---------- |
| size        | размер окна                      | ширина, длинна     |            |
| update_time | Время обновления данных виджетов | время в секундах   |            |

Пример:

```
size=1000, 800
update_time=0.1
```

Содержит раздел:

#### DataSourse:
Раздел содержит настройки для источников данных:

Настройки раздела:

| Название         | Описание             | Возможные значения | Примечания                                   |
| ---------------- | -------------------- | ------------------ | -------------------------------------------- |
| type             | Тип источника данных | строка             | соответствует имени соответствующего раздела |

Пример:

```
DataSourse\type=MAVLink
```
Содержит несколько разделов, соответствующих имеющимся типам источников данных:

##### Log
Раздел, отвечающий за настройки воспроизведения лог-файлов.

Настройки раздела:

| Название   | Описание                                | Возможные значения | Примечания                           |
| ---------- | --------------------------------------- | ------------------ | ------------------------------------ |
| path       | Путь до лог-файла                       | строка             |                                      |
| real_time  | востпризводить с учетом времени прихода | 2 - ВКЛ, 0 - ВЫКЛ  |                                      |
| time_delay | задержка между пакетами                 | время в секундах   |                                      |
| type       | тип лог-файла                           | строка             | на данный момент доступен только MAV |

Пример:

```
DataSourse\Log\path=./log/T6.mav
DataSourse\Log\real_time=2
DataSourse\Log\time_delay=0.05
DataSourse\Log\type=MAV
```

##### MAVLink
Раздел, отвечающий за настройки приема телеметрии с использованием протокола MAVLink

Настройки раздела:

| Название   | Описание             | Возможные значения | Примечания                                   |
| ---------- | -------------------- | ------------------ | -------------------------------------------- |
| connection | настройки соединения | строка             | соответствует настройке connection в mavutil |

Пример:

```
DataSourse\MAVLink\connection=udpin:0.0.0.0:14540
```