import argh
import logging
import glob


class Kmeans:

    def __init__(self, k=5, max_iter=100):
        self._k = k
        self._max_iter = max_iter
        self._centers = []
        self._points = []
        self._assignments = []
        self._distances = []
        self._logger = logging.getLogger(self.__class__.__name__)

    def step(self):
        # assignment step
        for point_id, x in enumerate(self._points):
            min_so_far = float("inf")
            argmin_so_far = -1
            for i, c in enumerate(self._centers):
                d = self.distance(c, x)
                if d < min_so_far:
                    min_so_far = d
                    argmin_so_far = i
            self._distances[point_id] = min_so_far
            self._assignments[point_id] = argmin_so_far

        # update step
        self._centers = [self.new_features() for _ in range(self._k)]
        counts = dict()
        for (x, a, d) in zip(self._points, self._assignments, self._distances):
            counts[a] = counts.get(a, 0) + 1
            c = self._centers[a]
            c = self.update_features(c, x)
            self._centers[a] = c

        for i, count in counts.items():
            c = self._centers[i]
            c = self.scale_features(c, 1.0/count)
            self._centers[i] = c

    def add_document(self, readable, max_iter=None):
        if max_iter is None: 
            max_iter = self._max_iter
        x = self.new_features()
        for line in readable:
            tokens = self.preprocess(line)
            x = self.update_features(x, self.new_features(tokens))
        self._points.append(x)
        if len(self._centers) < self._k:
            self._distances.append(0)
            self._assignments.append(len(self._centers))
            self._centers.append(x)
        else:
            self._distances.append(self.distance(x, self._centers[0]))
            self._assignments.append(0)
            for _iter in range(max_iter):
                self.info("starting iteration: {}".format(_iter))
                self.step()

    def info(self, *args):
        self._logger.info(*args)

    @staticmethod
    def preprocess(line):
        for word in line.split():
            yield word

    @staticmethod
    def new_features(tokens=tuple()):
        return {t: 1 for t in tokens}

    @staticmethod
    def update_features(x, y):
        return {
            key: x.get(key, 0) + y.get(key, 0)
            for key in set(x.keys()).union(y.keys())
        }

    @staticmethod
    def scale_features(x, f):
        return {k: v * f for (k, v) in x.items()}

    @staticmethod
    def distance(x, y):
        d = 0
        for key in set(x.keys()).union(y.keys()):
            d += abs(x.get(key, 0) - y.get(key, 0))
        return d

    def get_clusters(self):
        clusters = dict()
        for point, center in enumerate(self._assignments):
            points = clusters.get(center, list())
            points.append(point)
            clusters[center] = points
        return clusters

    def get_points(self):
        return self._points

    def get_centers(self):
        return self._centers


class LogCluster:

    def __init__(self, log_file_names):
        self._log_file_names = log_file_names

    def generate_files(self):
        for fn in self._log_file_names:
            with open(fn, "r") as f:
                yield f

    def cluster_logs(self):
        kmeans = Kmeans(k=5, max_iter=100)

        for f in self.generate_files():
            kmeans.add_document(f, max_iter=3)

        for _ in range(100):
            kmeans.step()

        clusters = kmeans.get_clusters()

        for center_id, point_ids in clusters.items():
            for point_id in point_ids:
                print("{}: {}".format(center_id, self._log_file_names[point_id]))


def test():

    kmeans = Kmeans(k=3)
    kmeans.add_document(["a lion sleeps"])
    kmeans.add_document(["a tiger runs"])
    kmeans.add_document(["a lion sleeps"])
    kmeans.add_document(["a tiger runs"])
    kmeans.add_document(["fish swim"])
    kmeans.add_document(["cat eats a fish"])

    centers = kmeans.get_centers()
    points = kmeans.get_points()

    for center_id, point_ids in kmeans.get_clusters().items():
        for point_id in point_ids:
            print("{}: {}".format(center_id, point_id))


def main(logs_glob):
    logging.basicConfig(level=logging.DEBUG)
    lc = LogCluster(glob.glob(logs_glob))
    lc.cluster_logs()


if __name__ == "__main__":
    p = argh.ArghParser()
    p.add_commands([main, test])
    p.dispatch()
