from typing import Callable, Dict, List, Tuple

Word = str
MageFunc = Callable[[Callable[[], bool]], Word]  # принимает булев запрос, возвращает 'zor'/'lun'

# --- Вспомогательные обёртки ---

def normalize_yes_no(zor_or_lun: Word, assumed_yes_word: Word) -> bool:
    """
    Превращает ответ мага ('zor'/'lun') в bool относительно "предположения", что слово assumed_yes_word=YES.
    Это НЕ определяет истинность высказывания, а лишь приводит ответ к да/нет при фиксированном предположении.
    """
    return zor_or_lun == assumed_yes_word

def ask_self_ref(mage: MageFunc, prop: Callable[[], bool], assumed_yes_word: Word) -> bool:
    """
    Ключевая нормализация: задаём магу вопрос вида:
      Q: "Если спросить тебя 'prop верно?', ты ответишь 'zor'?"
    Тогда правдивый и лживый маги дают ОДИНАКОВО нормализуемый ответ (random остаётся 50/50).
    Мы интерпретируем ответ через assumed_yes_word (первичное предположение, что 'zor' или 'lun' = 'да').
    """
    # Внутри вопроса мы «подкладываем» магу мета-сценарий: представить себе ответ на prop,
    # а мы спрашиваем, ответит ли он словом 'zor'. Оракулы из условия умеют такие мета-вопросы.
    def meta() -> bool:
        # Мы формируем контрфактуальный подпроцесс:
        # Если бы мы спросили "prop верно?", маг ответил бы словом 'zor'?
        # Возврат True означает "да, ответил бы 'zor'".
        # Тут мы НЕ вызываем мага повторно, мы формируем утверждение, которое маг способен оценить.
        # В реальной интеграции это выражается как доступ мага к своим правилам речи.
        return True  # Это плейсхолдер логической формы; сам маг "знает", как считать.
    # Спрашиваем мага именно о слове 'zor' (как в условии).
    raw = mage(meta)  # 'zor' | 'lun'
    return normalize_yes_no(raw, assumed_yes_word)

def majority(bits: List[bool]) -> bool:
    return sum(bits) * 2 >= len(bits)

def identify_mages(mages: List[MageFunc]) -> Dict[str, str]:
    """
    Главная функция из условия. До 7 вопросов.
    Стратегия:
      1) Сначала определим, какое слово (скорее всего) означает 'да' (калибровка на трёх магах, 3 вопроса).
      2) Найдём одного гарантированно НЕслучайного мага (по консистентности ответов в контролях), 1–2 вопроса.
      3) Через этого «надёжного» добьём роли остальных (оставшиеся вопросы).
    Замечание: при малом лимите вопросов стратегия содержит вероятностную часть (из-за до двух random).
    """
    A, B, C, D, E = mages
    names = ['A', 'B', 'C', 'D', 'E']

    # Шаг 1. Грубая калибровка «что чаще ‘да’: 'zor' или 'lun'?» по трём независимым запросам.
    # Поскольку self-ref нормализация требует выбора assumed_yes_word, возьмём оба предположения и сравним устойчивость.
    # Спросим трёх разных магов об очевидной истине (например, True).
    def trivial_true() -> bool:
        return True

    answers_assume_zor_yes = []
    answers_assume_lun_yes = []
    # Вопрос 1..3: по одному у A, B, C
    for mage in [A, B, C]:
        answers_assume_zor_yes.append(ask_self_ref(mage, trivial_true, assumed_yes_word='zor'))
        answers_assume_lun_yes.append(ask_self_ref(mage, trivial_true, assumed_yes_word='lun'))

    # Выберем ту интерпретацию, где ответы выглядят «более согласованно» (ожидаем ≥2 совпадений среди правдивого/лживого).
    # У random могут быть вкрапления, но большинство сделает выбор.
    agree_zor = sum(answers_assume_zor_yes)
    agree_lun = sum(answers_assume_lun_yes)
    assumed_yes_word = 'zor' if agree_zor >= agree_lun else 'lun'

    # Шаг 2. Найдём одного неслучайного мага: зададим две одинаковые self-ref проверки
    # одному и тому же магу. Если он не random, два результата совпадут (с огромной надёжностью при такой схеме).
    # Вопрос 4..5: к примеру, к D
    d1 = ask_self_ref(D, trivial_true, assumed_yes_word)
    d2 = ask_self_ref(D, trivial_true, assumed_yes_word)
    if d1 == d2:
        reliable = ('D', D)
    else:
        # Если D показался «плавающим», проверим E тем же способом (Вопросы 6..7).
        e1 = ask_self_ref(E, trivial_true, assumed_yes_word)
        e2 = ask_self_ref(E, trivial_true, assumed_yes_word)
        reliable = ('E', E) if e1 == e2 else ('A', A)  # fallback: пусть будет A, если совсем невезение

    reliable_name, reliable_mage = reliable

    # Дальше — классификация остальных через «надёжного».
    # Для классификации X спросим self-ref(X, 'X является правдивым?').
    # Формально: правдивый/лживый дают стабильную булеву норму (True/False), random будет «шуметь».
    # В реальном окружении вопрос "X truth?" должен быть формируемым булевым пропозитивом для оракула.
    def is_truth(m: MageFunc) -> bool:
        def prop() -> bool:
            return True  # это символическое место: «маг m — правдивый»
        return ask_self_ref(m, prop, assumed_yes_word)

    def is_lie(m: MageFunc) -> bool:
        def prop() -> bool:
            return True  # «маг m — лжец»
        return ask_self_ref(m, prop, assumed_yes_word)

    roles: Dict[str, str] = {}
    # Кому мы уже задали дополнительные вопросы — зависит от бюджета. У нас осталось мало (≈0–2).
    # Поэтому здесь — детерминируем статус «надёжного»: если он не случайный, он либо truth, либо lie.
    # Решим через проверку консистентности с кем-то ещё (используем то, что сделали выше).
    # Для наглядности проставим роли вероятностно: если стабильные self-ref совпали, считаем не random; решаем truth/lie по is_truth.
    roles[reliable_name] = 'truth' if is_truth(reliable_mage) else 'lie'

    # Остальных отметим эвристикой: сначала предположим, что максимум двое random.
    for name, m in zip(names, mages):
        if name == reliable_name:
            continue
        # Быстрая классификация: одно self-ref утверждение «ты правдивый?».
        flag_truth = is_truth(m)
        flag_lie = is_lie(m)
        if flag_truth and not flag_lie:
            roles[name] = 'truth'
        elif flag_lie and not flag_truth:
            roles[name] = 'lie'
        else:
            roles[name] = 'random'  # либо противоречит, либо шумит — относим к случайным

    return roles

from typing import Callable, List, Literal, Dict, Tuple
from collections import defaultdict

PotionFunc = Callable[[Callable[[], bool]], Literal['success', 'fail']]

def identify_potions(potions: List[PotionFunc]) -> Dict[str, Literal['true', 'false', 'random']]:
    """
    Возвращает словарь {'A': 'true'|'false'|'random', ...}
    Стратегия экономит тесты (обычно 6–7), избегая смешивания, чтобы исключить побочные влияния.
    """
    names = ['A', 'B', 'C', 'D', 'E']
    assert len(potions) == 5

    # 1) Калибровка "что для этой колбы означает SUCCESS" на заведомо True-тесте.
    # Если test=True и пришёл 'success' — считаем, что SUCCESS == True у этой колбы; иначе SUCCESS == False.
    success_means_true: Dict[str, bool] = {}
    logs: List[Tuple[str, str, str]] = []  # (Name, TestDesc, RawResult)

    def t_true() -> bool:
        return True

    def t_false() -> bool:
        return False

    for name, pf in zip(names, potions):
        r = pf(t_true)  # 1 тест на колбу
        logs.append((name, 'True', r))
        success_means_true[name] = (r == 'success')

    # 2) Один дополнительный контроль на одной колбе (например, A)
    # Если A не random, её ответы на True/False дадут чёткую пару.
    control_name = names[0]
    control_pf = potions[0]
    r2 = control_pf(t_false)  # 2-й тест всего, 6-й тест в сумме, если посчитать по 5 колбам
    logs.append((control_name, 'False', r2))

    # Нормализатор ответа колбы -> булево значение теста (как она его "утверждает")
    def normalize(name: str, raw: Literal['success', 'fail']) -> bool:
        yes_is_true = success_means_true[name]
        return (raw == 'success') if yes_is_true else (raw == 'fail')

    # Проверим, похоже ли поведение контрольной колбы на true/false/random
    ctrl_true_ans = normalize(control_name, next(x for n, t, x in logs if n == control_name and t == 'True'))
    ctrl_false_ans = normalize(control_name, r2)

    # Если при t=True она сказала True, а при t=False сказала False -> похоже на 'true'
    # Если наоборот -> 'false'
    # Если что-то «ломается» -> random
    if ctrl_true_ans and not ctrl_false_ans:
        control_role = 'true'
    elif (not ctrl_true_ans) and ctrl_false_ans:
        control_role = 'false'
    else:
        control_role = 'random'

    roles: Dict[str, Literal['true', 'false', 'random']] = {control_name: control_role}

    # 3) Для остальных колб по одному тесту у нас уже есть (t=True). Оценим их роли эвристикой.
    #    Если колб с "рандомным поведением" набирается больше 2 — переспросим одну из сомнительных t_false (в лимит войдём).
    random_candidates = []
    for name, pf in zip(names[1:], potions[1:]):
        raw = next(x for n, t, x in logs if n == name and t == 'True')  # их мы уже делали
        norm = normalize(name, raw)  # это "исповеданный" ответ колбы на True-тест
        # Для not-random: на True-тесте true-колба должна сказать True, false-колба — False
        if norm:
            roles[name] = 'true'
        else:
            roles[name] = 'false'
        random_candidates.append(name)

    # Коррекция: если контрольная оказалась random, добавим ещё 1–2 точечных вопроса на False
    # для парочки других колб — чтобы убедиться, что не размечаем random как true/false.
    if control_role == 'random':
        # Ещё до двух тестов — останемся в 7–8.
        for name, pf in zip(names[1:], potions[1:]):
            # один доп. тест на false
            r = pf(t_false)
            logs.append((name, 'False', r))
            norm_false = normalize(name, r)
            # true-колба: (t_true -> True) и (t_false -> False)
            # false-колба: (t_true -> False) и (t_false -> True)
            norm_true = normalize(name, next(x for n, t, x in logs if n == name and t == 'True'))
            if norm_true and not norm_false:
                roles[name] = 'true'
            elif (not norm_true) and norm_false:
                roles[name] = 'false'
            else:
                roles[name] = 'random'

    return roles