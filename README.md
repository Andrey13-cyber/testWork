# testWork

**Test**

Отправить и получить трафик, в данном случае - сообщение, для Multicast and Unicast on UDP.
Первым после компиляции запускается исполняемый файл программы testAns.cpp, вторым - test.cpp.
Для каждой программы компилируем и запускаем исполняемый файл в отдельном окне терминала.

При запуске исполняемого файла в терминале должны указываться два аргумента - Адрес и порт.
Для каждого исполняемого файла в командной строке указываем одинаковые адрес и порт для подключения к Multicast группе.
Например, ./testAns 226.1.1.1 10700
          ./test 226.1.1.1 10700
         
Локальный адрес Unicast задается, как local-host address "127.0.0.1".
В окне каждого исполняемго файла сначала появляется сообщение, что сокет создан.
Затем видим, что произошло подключение к мультикаст группе.
В окне исполянемого файла test вводим сообщение для передачи, в testAns видим, что нам пришло данное сообщение с мультикаст группы.
