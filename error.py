class Error:
    def __init__(self, error_code, details):
        self.error_code = error_code
        self.details = details

    def __str__(self):
        return f"{self.error_code}:{self.details}"


class IllegalCharError(Error):
    def __init__(self, details):
        super().__init__("IllegalCharError", details)

