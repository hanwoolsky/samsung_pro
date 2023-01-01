# [딕셔너리 - defaultdict] 값을 기정하지 않은 키는 그 값이 0으로 지정된다.
from collections import defaultdict
defaultdict(int) # 지정하지 않은 키는 값이 0으로 지정
defaultdict(list) # 지정하지 않은 키는 값이 []로 지정
defaultdict(set) # 지정하지 않은 키는 값이 set()로 지정
