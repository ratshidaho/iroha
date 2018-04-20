/**
 * Copyright Soramitsu Co., Ltd. 2018 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_TRANSACTION_STATUS_BUILDER_HPP
#define IROHA_TRANSACTION_STATUS_BUILDER_HPP

#include "interfaces/common_objects/account_asset.hpp"
#include "logger/logger.hpp"

namespace shared_model {
  namespace builder {

    // TODO: kamilsa 09.02.2018 IR-1087 Improve transaction status builder, so
    // that it is not allowed to set more than one status and transaction hash
    // is set before build method is invoked
    /**
     * Builder to construct transaction status object
     * @tparam BuilderImpl
     */
    template <typename BuilderImpl>
    class TransactionStatusBuilder {
     public:
      TransactionStatusBuilder() {
        log_ = logger::log("TransactionStatusBuilder");
      }

      std::shared_ptr<shared_model::interface::TransactionResponse> build() {
        log_->info("build status");
        return clone(builder_.build());
      }

      TransactionStatusBuilder statelessValidationSuccess() {
        log_->info("stateless success status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.statelessValidationSuccess();
        return copy;
      }

      TransactionStatusBuilder statelessValidationFailed() {
        log_->info("stateless failed status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.statelessValidationFailed();
        return copy;
      }

      TransactionStatusBuilder statefulValidationSuccess() {
        log_->info("stateful success status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.statefulValidationSuccess();
        return copy;
      }

      TransactionStatusBuilder statefulValidationFailed() {
        log_->info("stateful failed status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.statefulValidationFailed();
        return copy;
      }

      TransactionStatusBuilder committed() {
        log_->info("committed status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.committed();
        return copy;
      }

      TransactionStatusBuilder notReceived() {
        log_->info("not received status");
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.notReceived();
        return copy;
      }

      TransactionStatusBuilder txHash(const crypto::Hash &hash) {
        log_->info("status hash: {}", hash.hex());
        TransactionStatusBuilder copy(*this);
        copy.builder_ = this->builder_.txHash(hash);
        return copy;
      }

     private:
      BuilderImpl builder_;
      logger::Logger log_;
    };

  }  // namespace builder
}  // namespace shared_model

#endif  // IROHA_TRANSACTION_STATUS_BUILDER_HPP
