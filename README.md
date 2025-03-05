# wordle-data
- В этом проекте находятся общие файлы для других проектов wordle.
	- .proto файлы
	- перечисления
- А так же тесты для файлов.

## Сгенерировать файлы
```bash
git clone https://github.com/alec-chicherini/wordle-json.git
cd wordle-json
docker build --target=wordle_json_build . -t wordle-json-build
cd ~
```

## Запустить тесты
```bash
docker run --rm --privileged wordle-json-build
```