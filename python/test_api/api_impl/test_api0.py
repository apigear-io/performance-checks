from ..api_api import api
from ..api_api.shared import EventHook
#from api_api import api
#from api_api.shared import EventHook
from typing import Iterable

class TestApi0(api.ITestApi0):
    def __init__(self):
        super().__init__()
        self._prop_int: int = 0
        self._prop_float: float = 0.0
        self._prop_string: str = ""
        self.on_prop_int_changed: int = EventHook()
        self.on_prop_float_changed: float = EventHook()
        self.on_prop_string_changed: str = EventHook()
        self.on_sig_int = EventHook()
        self.on_sig_float = EventHook()
        self.on_sig_string = EventHook()

    def set_prop_int(self, value):
        if self._prop_int == value:
            return
        self._prop_int = value
        self._push_prop_int(self._prop_int)
    
    def get_prop_int(self):
        return self._prop_int        

    def _push_prop_int(self, value):
        self.on_prop_int_changed.fire(value)

    def set_prop_float(self, value):
        if self._prop_float == value:
            return
        self._prop_float = value
        self._push_prop_float(self._prop_float)
    
    def get_prop_float(self):
        return self._prop_float        

    def _push_prop_float(self, value):
        self.on_prop_float_changed.fire(value)

    def set_prop_string(self, value):
        if self._prop_string == value:
            return
        self._prop_string = value
        self._push_prop_string(self._prop_string)
    
    def get_prop_string(self):
        return self._prop_string        

    def _push_prop_string(self, value):
        self.on_prop_string_changed.fire(value)

    def func_int(self, param_int: int) -> int:
        return param_int

    def func_float(self, param_float: float) -> float:
        return 0.0

    def func_string(self, param_string: str) -> str:
        return ""

    def _sig_int(self, param_int: int):
        self.on_sig_int.fire(param_int)

    def _sig_float(self, param_float: float):
        self.on_sig_float.fire(param_float)

    def _sig_string(self, param_string: str):
        self.on_sig_string.fire(param_string)
