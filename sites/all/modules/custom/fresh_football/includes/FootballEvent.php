<?php

/**
 * @author Andrei Rusu <andrei.rusu@freshbyteinc.com>.
 */
class FootballEvent {

  /**
   * @return array
   */
  public function getRegisteredUsers() {
    $result = $this->buildQuery();


    if (isset($result['user'])) {
      $user_ids = array_keys($result['user']);
      $users = entity_load('user', $user_ids);

      return $this->buildResponse($this->generateTeams($users));
    }

    return array();
  }

  /**
   * @param $teams
   *
   * @return array
   */
  public function buildResponse($teams) {
    $response = array();

    foreach ($teams as $team) {
      $teamOutput = array();
      foreach ($team as $user) {
        $player = array();
        $player['name'] = $user->field_first_name[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_last_name[LANGUAGE_NONE][0]['value'];
        $player['picture'] = $user->picture;
        $player['skill'] = isset($user->field_skill[LANGUAGE_NONE][0]['value']) ? $user->field_skill[LANGUAGE_NONE][0]['value'] : 0;

        $teamOutput[] = $player;
      }
      $response['teams'][] = $teamOutput;
    }

    return $response;
  }

  /**
   * @return mixed
   */
  private function buildQuery() {
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'user')
      ->propertyCondition('uid', array('0', '1'), 'NOT IN')
      ->propertyCondition('status', '0', '<>')
      ->range(0, 10);

    return $query->execute();
  }

  /**
   * @param $users
   * @return array
   */
  private function generateTeams($users) {
    $users = array_values($users);
    //Knapsack algorithm
    $teams = $this->buildTeamsByRanking($users, 'field_skill');
    return $teams;
  }

  /**
   * @param $users
   *
   * @return array
   */
  protected function buildTeamsByRanking($users) {
    return $this->balance($users, 'field_skill');
  }

  /**
   * @param $items
   * @param $key
   *
   * @return array
   */
  private function balance($items, $key) {

    $maxWeight = floor($this->sum($items, $key) / 2);

    if (!$maxWeight) {
      return $this->generateNoSkillTeams($items);
    }

    $numItems = count($items);

    $sack = $this->buildSack($numItems, $maxWeight);

    for ($n = 1; $n <= $numItems; $n++) {
      // loop all items
      for ($weight = 1; $weight <= $maxWeight; $weight++) {
        $a = $sack[$n - 1][$weight]['value'];
        $b = NULL;
        $value = $items[$n - 1]->$key;
        if ($value <= $weight) {
          $b = $value + $sack[$n - 1][$weight - $value]['value'];
        }
        $sack[$n][$weight]['value'] = ($b === NULL ? $a : max($a, $b));
        $sack[$n][$weight]['take'] = ($b === NULL ? FALSE : $b > $a);
      }
    }

    $setA = array();
    $setB = array();

    for ($n = $numItems, $weight = $maxWeight; $n > 0; $n--) {
      $item = $items[$n - 1];
      $value = $item->$key;
      if ($sack[$n][$weight]['take']) {
        $setA[] = $item;
        $weight = $weight - $value;
      }
      else {
        $setB[] = $item;
      }
    }

    $this->reValidate($setA, $setB, $key);
    $this->reValidate($setA, $setB, $key, TRUE);
    $this->reValidate($setA, $setB, $key, TRUE, TRUE);

    return array($setA, $setB);
  }

  /**
   * @param $users
   *
   * @return array
   */
  private function generateNoSkillTeams($users) {
    $users = array_values($users);
    $playerNbr = count($users);
    if ($diff = $playerNbr % 2) {
      $teams = $this->balanceOdd($users, $playerNbr, $diff);
    }
    else {
      $teams = $this->balanceEven($users, $playerNbr);
    }

    return $teams;
  }

  /**
   * @param $users
   * @param $playerNbr
   *
   * @return array
   */
  protected function balanceEven($users, $playerNbr) {
    $mid = $playerNbr / 2;
    $team1 = array();
    $team2 = array();

    foreach ($users as $key => $user) {
      if ($key < $mid) {
        $team1[] = $user;
      }
      else {
        $team2[] = $user;
      }
    }

    return array(
      $team1,
      $team2,
    );
  }

  protected function balanceOdd($users, $playerNbr, $diff) {
    return $this->balanceEven($users, $playerNbr);
  }


  /**
   * @param $setA
   * @param $setB
   * @param string $key what key cotains the value
   * @param bool $approximate approximate values
   * @param bool $force - in case s**t
   */
  private function reValidate(&$setA, &$setB, $key, $approximate = FALSE, $force = FALSE) {
    $countA = count($setA);
    $countB = count($setB);
    if (abs($countA - $countB) > 1) {
      if ($countA > $countB) {
        $this->evenNumbers($setA, $setB, $key, $approximate, $force);
      }
      else {
        $this->evenNumbers($setB, $setA, $key, $approximate, $force);
      }
    }
  }

  /**
   * @param $items
   * @param $key
   *
   * @return int
   */
  private function sum($items, $key) {
    $sum = 0;
    foreach ($items as $item) {
      $val = isset($item->$key[LANGUAGE_NONE][0]['value']) ? $item->$key[LANGUAGE_NONE][0]['value'] : 0;
      $sum += $val;
    }
    return $sum;
  }

  /**
   * @param $width
   * @param $height
   *
   * @return array
   */
  private function buildSack($width, $height) {
    $sack = array();
    for ($x = 0; $x <= $width; $x++) {
      $sack[$x] = array();
      for ($y = 0; $y <= $height; $y++) {
        $sack[$x][$y] = array(
          'value' => 0,
          'take' => FALSE
        );
      }
    }
    return $sack;
  }

  /**
   * @param $bigTeam
   * @param $smallTeam
   * @param $key
   * @param bool $approximate
   * @param bool $force
   */
  private function evenNumbers(&$bigTeam, &$smallTeam, $key, $approximate = FALSE, $force = FALSE) {

    //TODO REMOVE FORCE - IS THIS NEEDED?
    if ($force) {
      $last = count($bigTeam) - 1;
      $bigTeam[] = $smallTeam[0];
      $smallTeam[] = $bigTeam[$last];
      $smallTeam[] = $bigTeam[$last - 1];
      unset($smallTeam[0], $bigTeam[$last], $bigTeam[$last - 1]);

      return;
    }

    $i = 0;
    do {
      $firstTrade = $bigTeam[$i];
      foreach (array_reverse($bigTeam, TRUE) as $j => $secondTrade) {
        $secondTrade = $bigTeam[$j];

        foreach ($smallTeam as $index => $player) {
          if ($approximate) {
            if ($this->approximateTradeCheck($player, $firstTrade, $secondTrade, $key)) {
              $bigTeam[] = $player;
              $smallTeam[] = $bigTeam[$i];
              $smallTeam[] = $bigTeam[$j];
              unset($smallTeam[$index], $bigTeam[$i], $bigTeam[$j]);
              break 3;
            }
          }
          else {
            if ($this->accurateTradeCheck($player, $firstTrade, $secondTrade, $key)) {
              $bigTeam[] = $player;
              $smallTeam[] = $bigTeam[$i];
              $smallTeam[] = $bigTeam[$j];
              unset($smallTeam[$index], $bigTeam[$i], $bigTeam[$j]);
              break 3;
            }
          }
        }
      }

      $i++;
    } while ($i < count($bigTeam));
  }

  /**
   * @param $player
   * @param $firstTrade
   * @param $secondTrade
   * @param $key
   * @return bool
   */
  private function accurateTradeCheck($player, $firstTrade, $secondTrade, $key) {
    $playerVal = isset($player->$key[LANGUAGE_NONE][0]['value']) ? $player->$key[LANGUAGE_NONE][0]['value'] : 0;
    $firstTradeVal = isset($firstTrade->$key[LANGUAGE_NONE][0]['value']) ? $firstTrade->$key[LANGUAGE_NONE][0]['value'] : 0;
    $secondTradeVal = isset($secondTrade->$key[LANGUAGE_NONE][0]['value']) ? $secondTrade->$key[LANGUAGE_NONE][0]['value'] : 0;
    return ($playerVal == $firstTradeVal + $secondTradeVal);
  }

  /**
   * @param $player
   * @param $firstTrade
   * @param $secondTrade
   * @param $key
   * @return bool
   */
  private function approximateTradeCheck($player, $firstTrade, $secondTrade, $key) {
    $playerVal = isset($player->$key[LANGUAGE_NONE][0]['value']) ? round($player->$key[LANGUAGE_NONE][0]['value']) : 0;
    $firstTradeVal = isset($firstTrade->$key[LANGUAGE_NONE][0]['value']) ? round($firstTrade->$key[LANGUAGE_NONE][0]['value']) : 0;
    $secondTradeVal = isset($secondTrade->$key[LANGUAGE_NONE][0]['value']) ? round($secondTrade->$key[LANGUAGE_NONE][0]['value']) : 0;
    return ($playerVal == $firstTradeVal + $secondTradeVal);
  }
}