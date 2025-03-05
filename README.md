# wordle-data
- В этом проекте находятся общие файлы для проекта wordle.
	- .proto файлы
	- перечисления
- А так же тесты для сгенерированных файлов на с++.

## Собрать тесты
```bash
git clone https://github.com/alec-chicherini/wordle-data.git
cd wordle-data
docker build --target=wordle_data_build . -t wordle-data-build
cd ~
```

## Запустить тесты
```bash
docker run --rm --privileged wordle-data-build
```