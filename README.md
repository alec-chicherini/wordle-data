# wordle-json
- В этом проекте находятся JSONSchem'ы проекта wordle.
- С помощью userver chaotic-gen генерируются с++ файлы для других проектов. 
- И запускаются тесты на сгенерированных файлах.

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