import sys
import time
import logging
from watchdog.observers import Observer
from watchdog.events import PatternMatchingEventHandler
import writeLogTitle 
class FileEventHandler(PatternMatchingEventHandler):
    def __init__(self):
        PatternMatchingEventHandler.__init__(self,ignore_patterns=["*.log"])
        writeLogTitle.writeLogTitle()
        logging.basicConfig(level=logging.DEBUG,
                format='%(asctime)s %(filename)s %(levelname)s %(message)s',
                datefmt='%a, %d %b %Y %H:%M:%S',
                filename='debug.log',
                filemode='a')
        console = logging.StreamHandler()
        console.setLevel(logging.INFO)
        formatter = logging.Formatter('%(name)-12s: %(levelname)-8s %(message)s')
        console.setFormatter(formatter)
        logging.getLogger('').addHandler(console)

    def on_moved(self, event):
        if event.is_directory:
            logging.debug("directory moved from {0} to {1}".format(
                event.src_path,event.dest_path))
        else:
            logging.debug("file moved from {0} to {1}".format(event.src_path,event.dest_path))

    def on_created(self, event):
        if event.is_directory:
            logging.debug("directory created:{0}".format(event.src_path))
        else:
            logging.debug("file created:{0}".format(event.src_path))

    def on_deleted(self, event):
        if event.is_directory:
            logging.debug("directory deleted:{0}".format(event.src_path))
        else:
            logging.debug("file deleted:{0}".format(event.src_path))

    def on_modified(self, event):
        if event.is_directory:
            logging.debug("directory modified:{0}".format(event.src_path))
        else:
            logging.debug("file modified:{0}".format(event.src_path))

if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else '.'
    event_handler = FileEventHandler()
    observer = Observer()
    observer.schedule(event_handler, path, recursive=True)
    observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()
