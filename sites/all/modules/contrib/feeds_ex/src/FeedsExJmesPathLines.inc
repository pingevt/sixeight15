<?php

/**
 * @file
 * Contains FeedsExJmesPathLines.
 */

/**
 * Parses JSON Lines documents with JMESPath.
 */
class FeedsExJmesPathLines extends FeedsExJmesPath {

  /**
   * The file iterator.
   *
   * @var FeedsExLineIterator
   */
  protected $iterator;

  /**
   * {@inheritdoc}
   */
  protected function executeContext(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    return $this->iterator;
  }

  /**
   * {@inheritdoc}
   */
  protected function hasConfigurableContext() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    parent::setUp($source, $fetcher_result);
    $this->iterator = new FeedsExLineIterator($fetcher_result->getFilePath());
    $this->iterator->setLineLimit($source->importer->getLimit());

    $state = $source->state(FEEDS_PARSE);
    if (!$state->total) {
      $state->total = $this->iterator->getSize();
    }

    $state->start = $state->pointer ? $state->pointer : 0;
    $this->iterator->setStartPosition($state->start);
  }

  /**
   * {@inheritdoc}
   */
  protected function cleanUp(FeedsSource $source, FeedsParserResult $result) {
    parent::cleanUp($source, $result);

    $state = $source->state(FEEDS_PARSE);
    $state->pointer = $this->iterator->ftell();

    unset($this->iterator);
  }

  /**
   * {@inheritdoc}
   */
  protected function executeSourceExpression($machine_name, $expression, $row) {
    // Row is a JSON string.
    if ($encoding = $this->detectEncoding($row)) {
      $row = $this->convertEncoding($row, $encoding);
    }
    $row = drupal_json_decode($row);
    $result = $this->jmesPath->search($expression, $row);

    if (is_scalar($result)) {
      return $result;
    }

    // Return a single value if there's only one value.
    return count($result) === 1 ? reset($result) : $result;
  }

}
