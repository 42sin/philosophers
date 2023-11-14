<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/42sin/philosophers">
    <img src="logo.png" alt="Logo" width="128" height="128">
  </a>

<h3 align="center">Philosophers</h3>

  <p align="center">
    The Dining Philosopher Problem
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

#### [Go to Subject PDF]
[![Subject PDF][subjectImage]](en.philo_subject.pdf)

This project is about the Dining Philosophers problem, which is a classic synchronization and concurrency problem that illustrates challenges in avoiding deadlock and ensuring the proper use of resources among multiple threads/processes. In this scenario, imagine five philosophers sitting around a dining table. Each philosopher alternates between thinking and eating. To eat, a philosopher needs both the left and right forks, which are placed between adjacent philosophers. The challenge is to design a solution that avoids deadlock (where no philosopher can finish eating) and ensures that philosophers can make progress without conflicts.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

The Project was tested on macOS, but it should work on all UNIX/LINUX based systems.

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/42sin/philosophers.git && cd philosophers
   ```
2. Compile (philo for threads & mutexes/philo_bonus for processes & semaphores)
   ```sh
   cd philo && make
   ```
3. Run
   ```sh
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[issues-url]: https://github.com/42sin/philosophers/issues
[license-url]: https://github.com/42sin/philosophers/blob/master/LICENSE
[subjectImage]: eval.png
[Go to Subject PDF]: en.philo_subject.pdf
