FROM python
COPY requirements.txt /
COPY x4controld.py /
RUN pip install -r /requirements.txt
ENTRYPOINT python /x4controld.py