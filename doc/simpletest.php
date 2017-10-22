<?php

// run like: php -d zend.assertions=1 -d assert.exception=1 sample.php

function getKVS($in) {
	return file_get_contents('http://localhost/myapi/kvs?R' . urlencode($in));
}

function setKVS($key, $value) {
	file_get_contents('http://localhost/myapi/kvs?W' . urlencode($key) . '&' . urlencode($value));
}

setKVS('abc', 'xyz');
assert(getKVS('abc') === 'xyz');

setKVS('あいうえお', '🐈한국어');
assert(getKVS('あいうえお') === '🐈한국어');

setKVS("aa\nb\0", "cc\rdd\x01");
assert(getKVS("aa\nb\0") === "cc\rdd\x01");

